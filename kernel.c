#include "kernel.h"
#include "font8x8_basic.h"

/*
 * Graphics Module Functionality:
 * Assume 32bit pixel format
*/

uint32_t lfb_address;
uint32_t verticalResolution;
uint32_t horizontalResolution;

//TODO: handle new line/carriage return
void kprint(const char *output)
{
    int current_line = 0;
    for (int i = 0; output[i] != '\0'; ++i) {
        drawChar(output[i], current_line, i*8);
    }
    // int current_line = 0;
    // int current_column = 0;
    // int character_index = 0;
    // char c = output[character_index++];
    // while (c != '\0') {
    //     if (c == '\n') {
    //         ++current_line;
    //         current_column = 0;
    //     } else {
    //         drawChar(c, current_line, current_column);
    //         ++current_column;
    //     }
    //     ++character_index;
    // }
}

//TODO support line number
void drawChar(char character, int line, int column)
{
    if (character < 0) {
        //ERROR: input
        return;
    }

    char *character_format = font8x8_basic[character];
    for (int p = 0; p < 8; ++p) {
        uint8_t character_line = character_format[p];
        for (int b = 0; b < 8; ++b) {
            uint8_t bit = character_line & 0b10000000;
            if (bit != 0) {
                setPixel(line * 8 + p, column + b, 0xFFFFFFFF);
            } else {
                // No print
            }
            character_line <<= 1;
        }
    }
}

void clear(uint8_t red, uint8_t green, uint8_t blue)
{
    Pixel pixel = createPixel(red, green, blue);
    for (int i = 0; i < verticalResolution; ++i) {
        for (int o = 0; o < horizontalResolution; ++o) {
            setPixel(i, o, pixel);
        }
    }
}

void setPixel(int r, int c, uint32_t rgb)
{
    r *= 4;
    c *= 4;
    uint32_t *addr = lfb_address + c + r * horizontalResolution;
    *addr = rgb | 0xff000000;
}


Pixel createPixel(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t pixel = 0;
    pixel = red;
    pixel <<= 8;
    pixel |= green;
    pixel <<= 8;
    pixel |= blue;
    return pixel;
}
