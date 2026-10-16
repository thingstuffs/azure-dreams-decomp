#include "common.h"
#include "m2c_compat.h"

extern s32 D_80155F90;

void func_80155C30(void) {
    *(u16 *)0x8001371A = 0;
    *(u16 *)0x80013718 = 0;
    *(u16 *)0x80013716 = 0;
    *(u16 *)0x80013714 = (*(u16 *)0x80013714 | 9) & 0xFFEF;
    *(u16 *)0x8001371C = (s32) D_80155F90;
}
