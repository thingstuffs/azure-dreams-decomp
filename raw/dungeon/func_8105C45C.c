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
extern u8 D_80173FD0[];
extern u8 D_80173FB8[];
extern s32 D_80083460[3];
extern s32 D_80170F68;
extern void *D_80170878[];
M2C_UNK func_800A2B04();
M2C_UNK func_800A48F0();
M2C_UNK func_800A4ACC();
M2C_UNK func_800A56E0();
s32 func_800A6D30();
extern u8 D_80173FD8;
extern M2C_UNK D_80173FE0;

void func_80173C5C(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6, &&jt_c7 };
    u8 *temp_a1;
    u16 *temp_counter;
    s32 temp_v1_3;
    u16 temp_v1_2;
    s32 temp_v1;
    s32 temp_v0;
    s32 temp_state;
    s32 temp_a0;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
    if (temp_v1 >= 8U) {
        goto block_20;
    }
    (void)jt_keep; goto *D_80170878[(u32)(temp_v1)];
jt_c0:
jt_c4:
    func_800A56E0(0x51C);
    temp_v1_2 = M2C_FIELD(arg2, u16 *, 0x14);
    if (!(temp_v1_2 & 0x8000)) {
        goto block_5;
    }
    M2C_FIELD(arg0, u8 *, 0x9B) = 7;
    goto block_20;
block_5:
    if (!(temp_v1_2 & 0xE000)) {
        goto block_20;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = &D_80173FD8;
    func_80047784(arg2, (&D_80173FD8)[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 8);
    M2C_FIELD(arg1, s32 *, 0x14) = 0xFFF00000;
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) & 0xF7FFFFFF);
    M2C_FIELD(arg0, s32 *, 0xA0) = 0;
    temp_state = M2C_FIELD(arg0, u8 *, 0x9B);
    temp_v1 = 10;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v1;
    goto block_e60;
jt_c1:
jt_c5:
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x90);
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xA0);
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg0, s32 *, 0x90) = temp_v0 - temp_v1_3;
    if (temp_a0 == 0) {
        goto block_10;
    }
    temp_v0 = temp_v1_3;
    temp_v1_3 = M2C_FIELD(arg1, s32 *, 0x14);
    M2C_FIELD(arg0, s32 *, 0xA0) = (s32) (temp_v0 + temp_v1_3);
    M2C_FIELD(arg1, s32 *, 0x14) = (s32) (M2C_FIELD(arg1, s32 *, 0x14) + 0x30000);
block_10:
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x90);
    temp_v1_3 = M2C_FIELD(arg0, s32 *, 0xA0);
    temp_a0 = M2C_FIELD(arg0, s16 *, 0x96);
    M2C_FIELD(arg0, s32 *, 0x90) = temp_v0 + temp_v1_3;
    if (temp_a0 > 0) {
        goto block_20;
    }
    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg3, s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x8000000);
    goto block_e5c;
jt_c2:
jt_c6:
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    M2C_FIELD(arg2, u8 **, 0x2C) = &D_80173FE0;
    func_80047784(arg2, ((u8 *) ((u32) ((((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7) + (u32) &D_80173FE0)))[0], 0);
    goto block_e5c;
jt_c3:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_20;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80173FD0;
    func_80047784(arg2, D_80173FD0[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    block_e5c:
    temp_state = M2C_FIELD(arg0, u8 *, 0x9B);
    block_e60:
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (temp_state + 1);
    goto block_20;
jt_c7:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_20;
    }
    M2C_FIELD(arg2, u8 **, 0x2C) = D_80173FB8;
    func_80047784(arg2, D_80173FB8[((s32) (*D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 9) & 7], 0);
    temp_counter = (u16 *) D_80083460;
    M2C_FIELD(temp_counter, u16 *, 0xA) = (u16) (M2C_FIELD(temp_counter, u16 *, 0xA) - 1);
    func_800A4ACC(arg3);
    M2C_FIELD(arg3, s8 *, 0x6D) = 0;
    M2C_FIELD(arg3, u16 *, 0x46) = (u16) (M2C_FIELD(arg3, u16 *, 0x46) & 0x7FFF);
    M2C_FIELD(arg0, s32 **, 0x8C) = &D_80170F68;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) | 0x8000);
    M2C_FIELD(arg0, s16 *, 0xAE) = (s16) ((func_800A6D30() & 7) + 8);
    func_800A48F0(arg3, 0x1A, (s8) M2C_FIELD(arg0, s16 *, 0xAE));
block_20:
    return;
}
