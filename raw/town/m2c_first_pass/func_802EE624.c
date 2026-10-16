#include "common.h"
#include "m2c_compat.h"

void func_80405624(void *arg0, void *arg1, void *arg2) {
    M2C_FIELD(arg1, s32 *, 0) = (s32) *(s32 *)0x8002D690;
    M2C_FIELD(arg1, s32 *, 4) = (s32) *(s32 *)0x8002D694;
    M2C_FIELD(arg1, s32 *, 8) = (s32) *(s32 *)0x8002D698;
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) *(s32 *)0x8002D69C;
    M2C_FIELD(arg2, s32 *, 0) = (s32) *(s32 *)0x8002D6A0;
    M2C_FIELD(arg2, s32 *, 4) = (s32) *(s32 *)0x8002D6A4;
    M2C_FIELD(arg2, s32 *, 8) = (s32) *(s32 *)0x8002D6A8;
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, void **, 8) = arg2;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 8) = -0xA0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xA) = -0x78;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xC) = 0x200;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0xF) = 4;
}
