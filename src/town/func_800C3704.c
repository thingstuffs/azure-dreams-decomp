#include "common.h"

u8 func_800C0E64(s32 arg0) {
    u8 *pg = (u8 *)0x80010000;
    return *(u8 *)(pg + arg0 * 2 + 0x33A4);
}
