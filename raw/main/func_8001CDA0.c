#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_8002D690[];
extern s32 D_8002D694[];
extern s32 D_8002D698[];
extern s32 D_8002D69C[];
extern s32 D_8002D6A0[];
extern s32 D_8002D6A4[];
extern s32 D_8002D6A8[];

void func_8001CDA0(void *arg0, void *arg1, void *arg2, s32 arg3) {
    s32 t;

    M2C_FIELD(arg1, s32 *, 0) = D_8002D690[0];
    t = D_8002D6A0[0];
    M2C_FIELD(arg1, s32 *, 4) = D_8002D694[0];
    M2C_FIELD(arg1, s32 *, 8) = D_8002D698[0];
    M2C_FIELD(arg1, s32 *, 0xC) = D_8002D69C[0];
    M2C_FIELD(arg2, s32 *, 0) = t;
    M2C_FIELD(arg2, s32 *, 4) = D_8002D6A4[0];
    M2C_FIELD(arg2, s32 *, 8) = D_8002D6A8[0];
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, void **, 8) = arg2;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 8) = -0xA0;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xA) = (s16) ((arg3 * 0x18) - 0x78);
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s16 *, 0xC) = 0x200;
    M2C_FIELD(M2C_FIELD(arg0, void **, 4), s8 *, 0xF) = 4;
}
