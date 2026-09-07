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

typedef struct EarlyCallData {
    u8 pad0[8];
    s32 value;
} EarlyCallData;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 D_800E3DA8[2];
s32 func_8003DE58();
s32 func_8004CAE8(s32, s32);
M2C_UNK func_80094E34();
s32 func_8009B88C();
M2C_UNK func_800A2B04();
M2C_UNK func_800A9A0C();
M2C_UNK func_800AACA4();
M2C_UNK func_8009A21C();
M2C_UNK func_800AA36C();
s16 func_800BCB04();

s32 func_800AC82C(void *arg0, void *arg1, void *arg2, void *arg3) {
    u16 sp18[3];
    u16 sp20;
    u16 sp22;
    M2C_UNK var_a2;
    s16 temp_v0_3;
    s32 temp_v0_4;
    u16 temp_a0;
    u16 temp_parent_u16;
    s32 temp_a1_2;
    s32 temp_v1_2;
    u16 temp_v0_2;
    s32 temp_v0_6;
    u8 temp_v1;
    u8 temp_x;
    u8 temp_y;
    void *temp_a1;
    void *temp_s2;
    void *temp_v0;
    void *temp_v0_5;

    M2C_FIELD(arg2, s16 *, 6) = 0;
    temp_v1 = M2C_FIELD(arg0, u8 *, 0x9B);
    if (temp_v1 != 0) {
        if (temp_v1 != 1) {
            return 0;
        }
        goto block_6;
    }
    temp_a1 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), EarlyCallData **, -0x14);
    if (func_8004CAE8(((EarlyCallData *) temp_a1)->value, 0) != 0) {
        M2C_FIELD(arg0, u8 *, 0x9B) = (u8) (M2C_FIELD(arg0, u8 *, 0x9B) + 1);
block_6:
        if (M2C_FIELD(arg3, s16 *, 0x64) < 0) {
            func_80094E34();
        }
        if (M2C_FIELD(arg3, s8 *, 0x6D) != 0) {
            func_800A9A0C(arg3);
        }
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x200000) {
            func_800AACA4(arg0, arg1, arg2, arg3);
            return 0;
        }
        temp_v0 = M2C_FIELD(arg3, void **, 0x60);
        temp_a1 = M2C_FIELD(temp_v0, void **, -0x14);
        temp_s2 = M2C_FIELD(temp_v0, void **, -0x18);
        M2C_FIELD(arg2, u8 *, 0x24) = (u8) M2C_FIELD(temp_a1, u8 *, 0x24);
        M2C_FIELD(arg2, u8 *, 0x25) = (u8) M2C_FIELD(temp_a1, u8 *, 0x25);
        if (!(M2C_FIELD(arg3, s32 *, 0x1C) & 0x80000)) {
            M2C_FIELD(arg1, s32 *, 0x10) = 0;
            M2C_FIELD(arg1, s32 *, 0xC) = 0;
            M2C_FIELD(arg0, u16 *, 0x98) = (u16) (M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7);
            temp_v0_2 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u16 *, 0x2A);
            M2C_FIELD(arg3, u16 *, 0x6A) = temp_v0_2;
            M2C_FIELD(arg2, u8 *, 0x24) = (u8) (M2C_FIELD(temp_a1, u8 *, 0x24) + *(u8 *) &D_8006CCD8[(temp_v0_2 >> 9) & 7]);
            M2C_FIELD(arg2, u8 *, 0x25) = (u8) (M2C_FIELD(temp_a1, u8 *, 0x25) + *(u8 *) &D_8006CCE8[((u16) M2C_FIELD(arg3, u16 *, 0x6A) >> 9) & 7]);
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            temp_v0_3 = func_800BCB04(M2C_FIELD(arg1, u16 *, 2), M2C_FIELD(arg1, u16 *, 6), (s16) (M2C_FIELD(arg3, u16 *, 0x88) - 0x20));
            if (temp_v0_3 < 0x200) {
                M2C_FIELD(arg0, s16 *, 0x92) = 0;
                M2C_FIELD(arg3, u16 *, 0x88) = (u16) temp_v0_3;
            }
            if ((func_8009B88C(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), &sp20, &sp22) << 0x10) != 0) {
                M2C_FIELD(arg2, u8 *, 0x24) = sp20;
                M2C_FIELD(arg2, u8 *, 0x25) = sp22;
                func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
                temp_v0_4 = M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000;
                M2C_FIELD(arg3, s32 *, 0x1C) = temp_v0_4;
                temp_x = M2C_FIELD(arg2, u8 *, 0x24);
                temp_y = M2C_FIELD(arg2, u8 *, 0x25);
                var_a2 = 0x3000;
                if (temp_v0_4 & 0x2000) {
                    var_a2 = 0x300;
                }
                func_8009A21C(temp_x, temp_y, var_a2);
                M2C_FIELD(arg3, s8 *, 0x71) = 0;
                return 1;
            }
            func_800A2B04(arg1, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
            func_800AA36C(arg0, arg1, arg2, arg3);
            return 0;
        }
        if (func_8003DE58(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, sp18, 0) != 0) {
            M2C_FIELD(arg1, u16 *, 2) = (u16) ((u16) *D_800E3DA8 + (M2C_FIELD(temp_s2, u16 *, 2) + sp18[0]));
            M2C_FIELD(arg1, u16 *, 6) = (u16) ((u16) D_800E3DA8[1] + (M2C_FIELD(temp_s2, u16 *, 6) + sp18[1]));
            temp_a0 = M2C_FIELD(M2C_FIELD(arg3, void **, 0x60), u16 *, 0x88);
            M2C_FIELD(arg3, u16 *, 0x88) = temp_a0;
            M2C_FIELD(arg0, s16 *, 0x92) = (s16) (((M2C_FIELD(temp_s2, u16 *, 0xA) + sp18[2]) - temp_a0) + 8);
            M2C_FIELD(arg2, s16 *, 6) = 0x10;
            M2C_FIELD(arg3, volatile s32 *, 0x1C) = (s32) (M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000000);
            temp_v0_5 = M2C_FIELD(arg3, void * volatile *, 0x60);
            temp_v1_2 = M2C_FIELD(arg3, s16 *, 0x6A);
            temp_parent_u16 = M2C_FIELD(temp_v0_5, volatile u16 *, 0x2A);
            temp_a1_2 = M2C_FIELD(temp_v0_5, s16 *, 0x2A);
            temp_v0_6 = M2C_FIELD(arg3, u16 *, 0x2A) - (temp_v1_2 - temp_a1_2);
            M2C_FIELD(arg3, u16 *, 0x6A) = temp_parent_u16;
            M2C_FIELD(arg3, s16 *, 0x2A) = temp_v0_6;
        }
        return 0;
    }
    return 0;
}
