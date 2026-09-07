#include "common.h"
typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern u8 D_80171E20[];
extern s32 D_8008346C[];
extern s16 D_80083228[5];
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80047784(void *, u8, s32);
extern u8 D_801753E4[];

void func_801735E8(void *arg0, void *arg1, void *arg2, void *arg3) {
    void *base0;
    u16 temp_v0;
    u16 temp_v0_2;
    s32 temp_v1;
    base0 = arg0;

    temp_v1 = M2C_FIELD(base0, u8 *, 0x9B);
    if (temp_v1 == 1) {
        goto state1;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0) {
            goto state0;
        }
        goto done;
    }
    if (temp_v1 == 2) {
        goto state2;
    }
    if (temp_v1 == 3) {
        goto state3;
    }
    goto done;

state0:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0x8000) {
        M2C_FIELD(base0, u8 *, 0x9B) = 3U;
        M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x6000);
        func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
        goto done;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0x0C) = 0;
    temp_v0 = M2C_FIELD(base0, u8 *, 0x9B);
    M2C_FIELD(base0, u16 *, 0x96) = 0U;
    M2C_FIELD(base0, u8 *, 0x9B) = (u8) (temp_v0 + 1);
    goto done;

state1:
        temp_v0_2 = M2C_FIELD(base0, u16 *, 0x96) + 1;
        M2C_FIELD(base0, u16 *, 0x96) = temp_v0_2;
    if ((s16) temp_v0_2 != 4 && !(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = &D_801753E4;
    func_80047784(arg2, D_801753E4[(((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7)], 0);
    func_800A56E0(0x808);
    temp_v0 = M2C_FIELD(base0, u8 *, 0x9B);
    M2C_FIELD(base0, u16 *, 0x96) = 0U;
    M2C_FIELD(base0, u8 *, 0x9B) = (u8) (temp_v0 + 1);
    goto done;

state2:
    temp_v0 = M2C_FIELD(base0, u16 *, 0x96) + 1;
    M2C_FIELD(base0, u16 *, 0x96) = temp_v0;
    if ((s16) temp_v0 != 4 && !(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto done;
    }
    func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1);
    temp_v0 = M2C_FIELD(base0, u8 *, 0x9B);
    M2C_FIELD(base0, u16 *, 0x96) = 0U;
    M2C_FIELD(base0, u8 *, 0x9B) = (u8) (temp_v0 + 1);
    goto done;

state3:
    if (M2C_FIELD(arg2, u16 *, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        M2C_FIELD(base0, u8 **, 0x8C) = D_80171E20;
        *D_8008346C = 0;
        func_800A4ACC(arg3);
        M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    }

done:
    return;
}
