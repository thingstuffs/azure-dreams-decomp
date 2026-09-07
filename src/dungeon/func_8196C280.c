#include "common.h"

typedef struct S_8196C280_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
} S_8196C280_0;   /* arg1 in func_8196C280 */

typedef struct S_8196C280_1 {
    u8 pad_00[0x2C];
    u16 unk_2C;
    u8 pad_2E[0x22];
    u16 unk_50;
    u8 pad_52[0x3A];
    s32 unk_8C;
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9C;
    s32 unk_A0;
} S_8196C280_1;   /* arg0 in func_8196C280 */

typedef struct S_8196C280_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8196C280_2;   /* arg2 in func_8196C280 */



typedef struct PositionRef {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} PositionRef;

extern s32 func_80024AF8();
extern s32 func_800A45D8();
extern s16 func_800BCB04();
extern s16 D_800269B4;
extern s32 D_800814A0;
extern PositionRef D_80083780;

void func_8196C280(void *arg0, void *arg1, void *arg2) {
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u16 raw_x ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 raw_y;
    u16 var_a0;
    register u16 var_v1 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    ((S_8196C280_0 *)arg1)->unk_00.at00.v += ((S_8196C280_1 *)arg0)->unk_8C;
    ((S_8196C280_1 *)arg0)->unk_8C += ((S_8196C280_1 *)arg0)->unk_98;
    {
        u16 call_x;
        u16 call_y;
        s32 call_z;

        call_x = ((S_8196C280_0 *)arg1)->unk_00.at02.v;
        call_y = ((S_8196C280_0 *)arg1)->unk_04.at02.v;
        call_z = ((S_8196C280_0 *)arg1)->unk_08.at02.v;
        D_800269B4 = 1;
        if ((func_800A45D8(call_x, call_y, call_z) << 0x10) != 0) {
            ((S_8196C280_0 *)arg1)->unk_00.at00.v -= ((S_8196C280_1 *)arg0)->unk_8C;
            ((S_8196C280_1 *)arg0)->unk_8C = 0;
            ((S_8196C280_1 *)arg0)->unk_98 = 0;
        }
    }
    ((S_8196C280_0 *)arg1)->unk_04.at00.v += ((S_8196C280_1 *)arg0)->unk_90;
    ((S_8196C280_1 *)arg0)->unk_90 += ((S_8196C280_1 *)arg0)->unk_9C;
    if ((func_800A45D8(((S_8196C280_0 *)arg1)->unk_00.at02.v, ((S_8196C280_0 *)arg1)->unk_04.at02.v, ((S_8196C280_0 *)arg1)->unk_08.at02.v) << 0x10) != 0) {
        ((S_8196C280_0 *)arg1)->unk_04.at00.v -= ((S_8196C280_1 *)arg0)->unk_90;
        ((S_8196C280_1 *)arg0)->unk_90 = 0;
        ((S_8196C280_1 *)arg0)->unk_9C = 0;
    }
    ((S_8196C280_0 *)arg1)->unk_08.at00.v += ((S_8196C280_1 *)arg0)->unk_94;
    ((S_8196C280_1 *)arg0)->unk_94 += ((S_8196C280_1 *)arg0)->unk_A0;
    {
        s32 temp_s0;

        temp_s0 = ((S_8196C280_0 *)arg1)->unk_08.at02.v;
        if ((func_800BCB04(((S_8196C280_0 *)arg1)->unk_00.at02.v, ((S_8196C280_0 *)arg1)->unk_04.at02.v, (s16)(((S_8196C280_0 *)arg1)->unk_08.at02u.v - 4)) - 0x10) < temp_s0) {
            ((S_8196C280_1 *)arg0)->unk_94 = 0;
            ((S_8196C280_1 *)arg0)->unk_90 = 0;
            ((S_8196C280_1 *)arg0)->unk_8C = 0;
            ((S_8196C280_0 *)arg1)->unk_08.at02.v = func_800BCB04(((S_8196C280_0 *)arg1)->unk_00.at02.v, ((S_8196C280_0 *)arg1)->unk_04.at02.v, (s16)(((S_8196C280_0 *)arg1)->unk_08.at02u.v - 4)) - 0x11;
            ((S_8196C280_0 *)arg1)->unk_08.at00u.v = 0;
            ((S_8196C280_1 *)arg0)->unk_2C = 0;
        }
    }
    temp_v0 = ((S_8196C280_1 *)arg0)->unk_50;
    ((S_8196C280_1 *)arg0)->unk_50 = temp_v0 + 1;
    if ((s16)temp_v0 >= 3) {
        raw_x = ((S_8196C280_2 *)arg2)->unk_1C;
        raw_y = ((S_8196C280_2 *)arg2)->unk_1E;
        temp_v0_2 = raw_x - 0x100;
        var_v1 = temp_v0_2;
        if ((s16)temp_v0_2 < 0) {
            var_v1 = 0;
        }
        temp_v0_3 = raw_y - 0x100;
        var_a0 = temp_v0_3;
        if ((s16)temp_v0_3 < 0) {
            var_a0 = 0;
        }
        if (((var_a0 << 0x10) == 0) || ((var_v1 << 0x10) == 0)) {
            ((S_8196C280_1 *)arg0)->unk_2C = 0;
        }
        ((S_8196C280_2 *)arg2)->unk_1C = var_v1;
        ((S_8196C280_2 *)arg2)->unk_1E = var_a0;
    }
    func_80024AF8(arg0, arg1, arg2,
        (s16)(((S_8196C280_0 *)arg1)->unk_00.at02.v - D_80083780.x),
        (s16)(((S_8196C280_0 *)arg1)->unk_04.at02.v - D_80083780.y),
        (s16)(((S_8196C280_0 *)arg1)->unk_08.at02u.v - D_80083780.z));
    temp_v0_4 = ((S_8196C280_1 *)arg0)->unk_2C - 1;
    ((S_8196C280_1 *)arg0)->unk_2C = temp_v0_4;
    if ((temp_v0_4 << 0x10) <= 0) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
    if (((S_8196C280_2 *)arg2)->unk_14 & 0x8000) {
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
