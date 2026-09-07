#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s16 D_80083228[5];
extern s32 D_8006CD58[];
extern s32 D_8003E140[];
struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 D_80083160;
extern u8 D_80045340[];
extern u8 D_8014A000[];
extern s16 D_80174F48[];
extern s32 D_800814A0[3];
extern s32 D_80083460[3];
extern void *D_80170870[];
M2C_UNK func_8003E4FC();
M2C_UNK func_8003F540();
void *func_8003FC64();
M2C_UNK func_80041588();
M2C_UNK func_8004491C();
M2C_UNK func_800445E0();
s32 func_8003DB94();
s32 func_80047738();
s32 rand();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
void *func_800A504C();
M2C_UNK func_800A56E0();
s32 func_800ADC4C();
M2C_UNK func_800C77D0();
M2C_UNK func_801745E0();
s32 func_800498A0(void *, ...);
extern u8 *D_800DCEEC[];
extern M2C_UNK D_800DCF5C;
extern M2C_UNK D_8017487C;
extern M2C_UNK D_80174FAC;
extern M2C_UNK D_80174FB4;
extern u8 D_80174FCC[];
extern u8 D_80174FCD[];
extern s32 D_80174FD0[];

void func_801749A8(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8 };
    M2C_UNK *temp_a1;
    s16 temp_a0;
    s32 temp_v0_2;
    s16 var_v1;
    u16 temp_v0;
    s16 temp_v0_3;
    u16 temp_v1_2;
    u8 temp_v1;
    u8 var_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_v1_3;
    u16 *temp_83460;

    temp_s0 = &D_80083160;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    var_v0 = temp_v1 < 9U;
    if (var_v0 == 0) {
        goto block_32;
    }
    (void)jt_keep; goto *D_80170870[(u32)(temp_v1)];
jt_c0:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8)(M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
jt_c1:
    func_80041588(&D_80174FAC, &D_80174FCC, 0);
    M2C_FIELD(arg0, s16 *, 0xA8) = 0;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(arg3, u16 *, 0x8A) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
jt_c2:
    temp_a0 = ((s32) (*D_80083228 + (s16) M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7;
    if (D_80174FCC[0] == 0) {
        goto block_7;
    }
    if (temp_a0 == 2) {
        goto block_10;
    }
block_7:
    if (temp_a0 == 2) {
        return;
    }
    temp_v0 = M2C_FIELD(arg3, u16 *, 0x2A) + 0x200;
    M2C_FIELD(arg3, u16 *, 0x2A) = temp_v0;
    return;
block_10:
    func_80041588(&D_80174FAC, &D_80174FCC, 1);
    func_8003F540(0, *D_8006CD58, 0x04000AD4, 0x05000CC4);
    func_8003E4FC(0x15, func_800445E0(), NULL);
    D_80174FCD[0] = 0;
    func_8003E4FC(0xFF, (s32) D_8003E140, &D_80174FCD);
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c3:
    temp_v1_2 = M2C_FIELD(arg0, u16 *, 0x96);
    temp_v0 = temp_v1_2 - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        goto block_15;
    }
    var_v0 = D_80174FCD[0];
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v1_2;
    if (var_v0 == 0) {
        return;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A56E0(0x300);
    return;
block_15:
    temp_a1 = D_800DCEEC[func_800498A0(arg3)];
    M2C_FIELD(temp_s0, u8 *, 0xA8) = (u8) (M2C_FIELD(temp_s0, u8 *, 0xA8) + ((s32) (M2C_FIELD(temp_a1, u8 *, 0) - M2C_FIELD(temp_s0, u8 *, 0xA8)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    M2C_FIELD(temp_s0, u8 *, 0xA9) = (u8) (M2C_FIELD(temp_s0, u8 *, 0xA9) + ((s32) (M2C_FIELD(temp_a1, u8 *, 1) - M2C_FIELD(temp_s0, u8 *, 0xA9)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    M2C_FIELD(temp_s0, u8 *, 0xAA) = (u8) (M2C_FIELD(temp_s0, u8 *, 0xAA) + ((s32) (M2C_FIELD(temp_a1, u8 *, 2) - M2C_FIELD(temp_s0, u8 *, 0xAA)) / (s16) M2C_FIELD(arg0, u16 *, 0x96)));
    return;
jt_c4:
    temp_s0 = func_8003FC64(0x12);
    if (temp_s0 == 0) {
        goto block_32;
    }
    M2C_FIELD(temp_s0, M2C_UNK **, 0x10) = &D_8017487C;
    func_8004491C(temp_s0, D_80045340);
    M2C_FIELD(arg0, void **, 0xA4) = temp_s0;
    M2C_FIELD(M2C_FIELD(temp_s0, void **, 8), s32 *, 0) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(M2C_FIELD(temp_s0, void **, 8), s32 *, 4) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(M2C_FIELD(temp_s0, void **, 8), s32 *, 8) = (s32) M2C_FIELD(arg1, s32 *, 8);
    temp_s0 = M2C_FIELD(temp_s0, void **, 0xC);
    M2C_FIELD(temp_s0, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(temp_s0, s16 *, 0x1C) = 0x1000;
    M2C_FIELD(temp_s0, s32 *, 0xC) = 0x808080;
    temp_v0_2 = func_800498A0(arg3) - 1;
    var_v1 = temp_v0_2;
    if ((temp_v0_2 << 0x10) >= 0) {
        goto block_20;
    }
    var_v1 = rand() % 3;
block_20:
    func_8003DB94(temp_s0, &D_8014A000[*(((s32) (var_v1 << 0x10) >> 0x10) + &D_80174FB4)], 0);
    M2C_FIELD(arg2, u16 *, 0x14) = (u16) (M2C_FIELD(arg2, u16 *, 0x14) | 0x80);
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_801745E0(arg0, arg1, arg2);
    return;
jt_c5:
    temp_s0 = M2C_FIELD(arg0, void **, 0xA4);
    temp_s0 = M2C_FIELD(temp_s0, void **, 0xC);
    if (!(M2C_FIELD(temp_s0, u16 *, 0x14) & 0xE000)) {
        goto block_24;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c6:
block_24:
    if (M2C_FIELD(arg0, u8 *, 0x9B) != 6) {
        return;
    }
    temp_v0_2 = func_800ADC4C(arg1, D_80174FD0[0], D_80174F48[0], &D_800DCF5C);
    if (temp_v0_2 == 0) {
        goto block_32;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    func_800A18E8(M2C_FIELD(arg3, u8 *, 0x13), 3);
    func_8009A3D0(M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), 0x300);
    func_8009A028(arg3);
    temp_s0 = arg3 - 0x20;
    M2C_FIELD(temp_s0, s32 *, 0x10) = M2C_FIELD(temp_s0, s32 *, 0x10) | 0x80000000;
    return;
jt_c7:
    temp_v0_2 = func_800A504C(arg2, arg3);
    M2C_FIELD(arg3, void **, 0x60) = (void *) temp_v0_2;
    if (temp_v0_2 == 0) {
        goto block_32;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0x10U;
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u16 *, 0x2A) = (u16) M2C_FIELD(arg3, u16 *, 0x2A);
    temp_v1_3 = M2C_FIELD(arg3, void **, 0x60);
    temp_s0_2 = M2C_FIELD(temp_v1_3, void **, -0x14);
    func_80047738(temp_s0_2, *(M2C_FIELD(temp_s0_2, u8 **, 0x2C) + (((s32) (*D_80083228 + (s16) M2C_FIELD(temp_v1_3, u16 *, 0x2A) + 0x100) >> 9) & 7)), M2C_FIELD(temp_s0_2, s8 *, 4));
    M2C_FIELD(temp_s0_2, u16 *, 0x14) = (u16) (M2C_FIELD(temp_s0_2, u16 *, 0x14) & 0xFFFE);
jt_c8:
    temp_v0_3 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0_3;
    if (temp_v0_3 > 0) {
        goto block_32;
    }
    M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u16 *, 0x2A) = (u16) M2C_FIELD(arg3, u16 *, 0x8A);
    M2C_FIELD(arg0, u16 *, -2) = (u16) (M2C_FIELD(arg0, u16 *, -2) | 0x8000);
    D_800814A0[0] = D_800814A0[0] | 0x8000;
    temp_83460 = (u16 *)&D_80083460;
    temp_83460[5] = (u16)(temp_83460[5] - 1);
    M2C_FIELD(arg3, s8 *, 0x6D) = 0;
block_32:
    return;
}
