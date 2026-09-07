#include "common.h"

typedef struct S_8017142C_0 {
    s16 unk_00;
    u8 pad_02[0x18];
    s16 unk_1A;
    u8 pad_1C[0x8];
    u16 unk_24;
    u16 unk_26;
    u8 pad_28[0x38];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
    s32 unk_74;
} S_8017142C_0;   /* arg0 in func_8017142C */

typedef struct S_8017142C_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_8017142C_1;   /* arg1 in func_8017142C */

typedef struct S_8017142C_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8017142C_2;   /* arg2 in func_8017142C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800478B8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s32 D_800814A0;

void func_8017142C(void *arg0, void *arg1, void *arg2) {
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s4;
    s32 temp_lo;
    s32 temp_v0;
    s32 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    u16 temp_v0_5;
    u16 temp_v0_6;
    u16 temp_v0_7;
    u16 temp_v0_8;
    u16 temp_v0_9;

    if (((S_8017142C_0 *)arg0)->unk_00 == 0) {
        ((S_8017142C_1 *)arg1)->unk_00.at00.v += ((S_8017142C_0 *)arg0)->unk_60;
        temp_v0 = ((S_8017142C_0 *)arg0)->unk_60;
        ((S_8017142C_0 *)arg0)->unk_60 = (temp_v0 * 2) / 3;
        if ((func_800A45D8(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, ((S_8017142C_1 *)arg1)->unk_08.at02.v) << 0x10) != 0) {
            ((S_8017142C_1 *)arg1)->unk_00.at00.v -= ((S_8017142C_0 *)arg0)->unk_60;
            ((S_8017142C_0 *)arg0)->unk_60 = 0;
            ((S_8017142C_0 *)arg0)->unk_6C = 0;
        }
        ((S_8017142C_1 *)arg1)->unk_04.at00.v += ((S_8017142C_0 *)arg0)->unk_64;
        temp_v0_2 = ((S_8017142C_0 *)arg0)->unk_64;
        ((S_8017142C_0 *)arg0)->unk_64 = (temp_v0_2 * 2) / 3;
        if ((func_800A45D8(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, ((S_8017142C_1 *)arg1)->unk_08.at02.v) << 0x10) != 0) {
            ((S_8017142C_1 *)arg1)->unk_04.at00.v -= ((S_8017142C_0 *)arg0)->unk_64;
            ((S_8017142C_0 *)arg0)->unk_64 = 0;
            ((S_8017142C_0 *)arg0)->unk_70 = 0;
        }
        ((S_8017142C_1 *)arg1)->unk_08.at00.v += ((S_8017142C_0 *)arg0)->unk_68;
        ((S_8017142C_0 *)arg0)->unk_68 += ((S_8017142C_0 *)arg0)->unk_74;
        temp_s0 = ((S_8017142C_1 *)arg1)->unk_08.at02.v;
        if ((func_800BCB04(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)arg1)->unk_08.at02.v - 4)) - 0x10) < temp_s0) {
            ((S_8017142C_0 *)arg0)->unk_68 = 0;
            ((S_8017142C_1 *)arg1)->unk_08.at02.v = func_800BCB04(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)arg1)->unk_08.at02.v - 4)) - 0x11;
            ((S_8017142C_1 *)arg1)->unk_08.at00u.v = 0;
            if (((S_8017142C_0 *)arg0)->unk_1A == 0) {
                ((S_8017142C_0 *)arg0)->unk_1A = 1;
                ((S_8017142C_0 *)arg0)->unk_24 = 0;
            }
        }
        temp_v0_3 = ((S_8017142C_0 *)arg0)->unk_26 + 1;
        ((S_8017142C_0 *)arg0)->unk_26 = temp_v0_3;
        if (!(temp_v0_3 & 3)) {
            func_800478B8(arg2);
        }
        temp_v0_4 = ((S_8017142C_2 *)arg2)->unk_1C + 0x64;
        ((S_8017142C_2 *)arg2)->unk_1C = temp_v0_4;
        if ((u32)(temp_v0_4 & 0xFFFF) >= 0x2001U) {
            ((S_8017142C_2 *)arg2)->unk_1C = 0x2000;
        }
        temp_v0_5 = ((S_8017142C_2 *)arg2)->unk_1E + 0x64;
        ((S_8017142C_2 *)arg2)->unk_1E = temp_v0_5;
        if ((u32)(temp_v0_5 & 0xFFFF) >= 0x2001U) {
            ((S_8017142C_2 *)arg2)->unk_1E = 0x2000;
        }
        temp_v0_6 = ((S_8017142C_0 *)arg0)->unk_24 - 1;
        ((S_8017142C_0 *)arg0)->unk_24 = temp_v0_6;
        if ((temp_v0_6 << 0x10) <= 0) {
            ((S_8017142C_0 *)arg0)->unk_1A = 0;
            ((S_8017142C_0 *)arg0)->unk_00 = (u16)((S_8017142C_0 *)arg0)->unk_00 + 1;
        }
        if (((S_8017142C_2 *)arg2)->unk_14 & 0x8000) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
    temp_s4 = ((S_8017142C_0 *)arg0)->unk_00;
    if (temp_s4 == 1) {
        if (((S_8017142C_0 *)arg0)->unk_1A == 0) {
            ((S_8017142C_0 *)arg0)->unk_1A = temp_s4;
            ((S_8017142C_0 *)arg0)->unk_24 = 0x14;
            ((S_8017142C_0 *)arg0)->unk_26 = 0x14;
            ((S_8017142C_0 *)arg0)->unk_64 = 0;
            ((S_8017142C_0 *)arg0)->unk_60 = 0;
        }
        temp_v0_7 = ((S_8017142C_2 *)arg2)->unk_1C + 0xC8;
        ((S_8017142C_2 *)arg2)->unk_1C = temp_v0_7;
        if ((u32)(temp_v0_7 & 0xFFFF) >= 0x2001U) {
            ((S_8017142C_2 *)arg2)->unk_1C = 0x2000;
        }
        temp_v0_8 = ((S_8017142C_2 *)arg2)->unk_1E + 0xC8;
        ((S_8017142C_2 *)arg2)->unk_1E = temp_v0_8;
        if ((u32)(temp_v0_8 & 0xFFFF) >= 0x2001U) {
            ((S_8017142C_2 *)arg2)->unk_1E = 0x2000;
        }
        ((S_8017142C_1 *)arg1)->unk_08.at00.v += ((S_8017142C_0 *)arg0)->unk_68;
        ((S_8017142C_0 *)arg0)->unk_68 += ((S_8017142C_0 *)arg0)->unk_74;
        temp_s0_2 = ((S_8017142C_1 *)arg1)->unk_08.at02.v;
        if ((func_800BCB04(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)arg1)->unk_08.at02.v - 4)) - 0x10) < temp_s0_2) {
            ((S_8017142C_0 *)arg0)->unk_68 = 0;
            ((S_8017142C_1 *)arg1)->unk_08.at02.v = func_800BCB04(((S_8017142C_1 *)arg1)->unk_00.at02.v, ((S_8017142C_1 *)arg1)->unk_04.at02.v, (s16)((u16)((S_8017142C_1 *)arg1)->unk_08.at02.v - 4)) - 0x11;
            ((S_8017142C_1 *)arg1)->unk_08.at00u.v = 0;
            if (((S_8017142C_0 *)arg0)->unk_1A == 0) {
                ((S_8017142C_0 *)arg0)->unk_1A = temp_s4;
                ((S_8017142C_0 *)arg0)->unk_24 = 0;
            }
        }
        temp_lo = ((s16)((S_8017142C_0 *)arg0)->unk_24 << 7) / (s16)((S_8017142C_0 *)arg0)->unk_26;
        ((S_8017142C_2 *)arg2)->unk_0E = 0;
        ((S_8017142C_2 *)arg2)->unk_0D = temp_lo;
        ((S_8017142C_2 *)arg2)->unk_0C = temp_lo;
        temp_v0_9 = ((S_8017142C_0 *)arg0)->unk_24 - 1;
        ((S_8017142C_0 *)arg0)->unk_24 = temp_v0_9;
        if ((temp_v0_9 << 0x10) <= 0) {
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
