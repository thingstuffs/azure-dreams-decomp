#include "common.h"

/* Writes the bytes 0x12, 0x10, and 0, then returns the next output position. */
void *func_800999B0(void *dst) {
    *(u8 *)dst = 0x12;
    dst = (u8 *)dst + 1;
    *(u8 *)dst = 0x10;
    dst = (u8 *)dst + 1;
    *(u8 *)dst = 0;
    return (u8 *)dst + 1;
}
