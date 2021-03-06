#include "graphics.h"
#include "font8x8_basic.h"

/*
 * Graphics Module Functionality:
 * Assume 32bit pixel format
*/

uint32_t* lfb_address;
uint32_t verticalResolution;
uint32_t horizontalResolution;

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
            uint8_t bit = character_line & 0b00000001;
            if (bit != 0) {
                setPixel(line * 8 + p, 8*column + b, 0xFFFFFFFF);
            } else {
                // No print
            }
            character_line >>= 1;
        }
    }
}

void clear(uint8_t red, uint8_t green, uint8_t blue)
{
    fillRect(red, green, blue, horizontalResolution, verticalResolution);

}

//TODO: fix
void fillRect(uint8_t red, uint8_t green, uint8_t blue, uint32_t width, uint32_t height)
{
    uint32_t *addr = lfb_address;
    Pixel pixel = createPixel(red, green, blue);
    for (int i = 0; i < height; ++i) {
        for (int o = 0; o < width; ++o) {
            addr[o + i*horizontalResolution] = pixel;
        }
    }
}

void setPixel(int r, int c, uint32_t rgb)
{
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
