#include "common.h"

extern u8 D_80127A40[];

s32 func_80123200(s32 arg0) {
    u8 value;

    arg0 &= 0xFF;
    value = D_80127A40[arg0];
    return (*(u8 *)(0x80013614 + (value >> 2)) >> ((value & 3) * 2)) & 1;
}
