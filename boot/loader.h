#ifndef BL_LOADER_H
#define BL_LOADER_H
#include <efi.h>
#include <efilib.h>

#include "elf.h"

void load_kernel(EFI_HANDLE ImageHandle);
void open_kernel_image(EFI_HANDLE ImageHandle, EFI_FILE_PROTOCOL **file);

void parse_ehdr(void * const buf, Elf64_Ehdr *header);
void parse_phdr(void * const buffer, Elf64_Ehdr ehdr, Elf64_Phdr **phdr);

void elf_load_phdr_buffer(void * const buf, int num, Elf64_Phdr *p_headers);

void print_ehdr(void *buf);

#endif