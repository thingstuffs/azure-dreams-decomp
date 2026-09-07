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

extern void *D_80088B50[];
void func_8003DB94();
M2C_UNK func_80099F04();
s32 func_8009C12C();
M2C_UNK func_800A2B04();
M2C_UNK func_800C77D0();
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern s16 D_80083228;
extern u8 D_80083460[16];
extern M2C_UNK D_80096384;
extern M2C_UNK D_800DD274[8];
extern M2C_UNK D_800DD294[8];

void func_800974DC(void *arg0, void *arg1, void *arg2, void *arg3) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 temp_v1_2;
    u16 temp_v0;
    s32 temp_v0_4;
    u8 temp_v1;
    void *temp_a2;
    u8 *temp_v0_2;

    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 >= 5U) {
        goto block_23;
    }
    (void)jt_keep; goto *D_80088B50[(u32)(temp_v1)];
jt_c0:
    func_800C77D0(arg3 - 0x20, arg1, 8, 0x300);
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_800DD294;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD294 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C)), 0);
    temp_v1_2 = ((u16) M2C_FIELD(arg3, s16 *, 0x2A) >> 8) & 0xE;
    M2C_FIELD(arg1, s32 *, 0xC) = (s32) (*(s16 *)((u8 *)D_8006CCD8 + temp_v1_2) << 0x11);
    temp_v0_4 = *(s16 *)((u8 *)D_8006CCE8 + temp_v1_2);
    M2C_FIELD(arg1, s32 *, 0x14) = 0xFFEBC000;
    M2C_FIELD(arg1, s32 *, 0x10) = (s32) (temp_v0_4 << 0x11);
    M2C_FIELD(arg0, u16 *, 0x96) = 3U;
    M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
jt_c1:
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_5;
    }
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
    goto block_6;
block_5:
    M2C_FIELD(arg0, u16 *, 0x96) = (u16) (M2C_FIELD(arg0, u16 *, 0x96) - 1);
block_6:
    if (M2C_FIELD(arg0, s16 *, 0x96) != 0) {
        goto block_12;
    }
    if (M2C_FIELD(arg0, u8 *, 0x102) != 0) {
        goto block_11;
    }
    M2C_FIELD(arg3, s16 *, 0x20) = 1;
    if (func_8009C12C(arg3, arg2, M2C_FIELD(arg3, s16 *, 0x2A), 1) != 0) {
        goto block_11;
    }
    temp_a2 = M2C_FIELD(arg3, void **, 0x60);
    if (temp_a2 == NULL) {
        goto block_11;
    }
    M2C_FIELD(arg3, void **, 0x60) = NULL;
    M2C_FIELD(temp_a2, s32 *, 0x1C) = (s32) (M2C_FIELD(temp_a2, s32 *, 0x1C) & 0xEFFFFFFF);
    M2C_FIELD(M2C_FIELD(temp_a2, void **, -0x14), s32 *, 0xC) = 0x808080;
block_11:
block_12:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) > 0) {
        goto block_15;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_15;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_800DD274;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C)), 0);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
jt_c2:
block_15:
    if (!(M2C_FIELD(arg0, u16 *, 0xA2) & 0x10)) {
        goto block_23;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    if ((s16) M2C_FIELD(arg0, u16 *, 0x96) > 0) {
        goto block_23;
    }
    M2C_FIELD(arg2, M2C_UNK **, 0x2C) = D_800DD274;
    func_8003DB94(arg2, *(M2C_UNK *)((u8 *)D_800DD274 + (((s32) (D_80083228 + M2C_FIELD(arg3, s16 *, 0x2A) + 0x100) >> 7) & 0x1C)), 0);
    M2C_FIELD(arg0, u8 *, 0x9B) = 3U;
    return;
jt_c3: {
    s32 coord;
    u32 delta;
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0xE000)) {
        goto block_23;
    }
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg0, u16 *, 0x96) = 2U;
    delta = (u32)M2C_FIELD(arg2, u8 *, 0x24) << 6;
    coord = M2C_FIELD(arg1, s16 *, 2) - 0x20;
    delta -= (u32)coord;
    M2C_FIELD(arg1, s32 *, 0xC) = (s32)(delta * 0x10000U) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
    coord = M2C_FIELD(arg1, s16 *, 6) - 0x20;
    delta = ((u32)M2C_FIELD(arg2, u8 *, 0x25) << 6) - (u32)coord;
    M2C_FIELD(arg1, s32 *, 0x10) = (s32)(delta * 0x10000U) / (s16) M2C_FIELD(arg0, u16 *, 0x96);
    M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
    return;
}
jt_c4:
    temp_v0 = M2C_FIELD(arg0, u16 *, 0x96) - 1;
    M2C_FIELD(arg0, u16 *, 0x96) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        goto block_22;
    }
    if (!(M2C_FIELD(arg2, u16 *, 0x14) & 0x8000)) {
        goto block_23;
    }
block_22:
    M2C_FIELD(arg1, s32 *, 0x14) = 0;
    M2C_FIELD(arg1, s32 *, 0x10) = 0;
    M2C_FIELD(arg1, s32 *, 0xC) = 0;
    func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    func_80099F04(M2C_FIELD(arg3, s32 *, 0x5C));
    temp_v0_2 = D_80083460;
    M2C_FIELD(temp_v0_2, u16 *, 2) = (u16) (M2C_FIELD(temp_v0_2, u16 *, 2) | 0x412);
    M2C_FIELD(arg0, M2C_UNK **, 0x8C) = &D_80096384;
    M2C_FIELD(temp_v0_2, s32 *, 0xC) = 0;
    M2C_FIELD(arg0, u16 *, 0x96) = 0U;
block_23:
    return;
}
