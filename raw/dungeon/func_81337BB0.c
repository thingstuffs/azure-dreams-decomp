#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80173C88;

void func_8016EBB0(s32 arg0) {
    *(u16 *)0x8001371A = 0;
    *(u16 *)0x80013718 = 0;
    *(u16 *)0x80013716 = 0;
    *(u16 *)0x80013714 = (*(u16 *)0x80013714 | 9) & 0xFFEF;
    *(u16 *)0x8001371C = (s32) *((arg0 * 4) + &D_80173C88);
}
