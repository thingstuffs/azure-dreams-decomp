#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800247C0_0 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800247C0_0;   /* arg0 in func_800247C0 */

typedef struct S_800247C0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800247C0_1;   /* temp_s2 in func_800247C0 */

typedef struct S_800247C0_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800247C0_2;   /* arg1 in func_800247C0 */

typedef struct S_800247C0_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800247C0_3;   /* temp_a0 in func_800247C0 */

typedef struct S_800247C0_4 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    union { u16 s; s16 u; } unk_1C;   /* accessed as both */
    union { u16 s; s16 u; } unk_1E;   /* accessed as both */
} S_800247C0_4;   /* temp_s1 in func_800247C0 */

typedef struct S_800247C0_5 {
    u8 pad_00[0x28];
    s16 unk_28;
    u8 pad_2A[0x5E];
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;
} S_800247C0_5;   /* temp_s0 in func_800247C0 */

typedef struct S_800247C0_6 {
    u8 pad_00[0x10];
    void * unk_10;
} S_800247C0_6;   /* global_base in func_800247C0 */

typedef struct S_800247C0_7 {
    u8 pad_00[0x28];
    s8 unk_28;
    u8 pad_29[0x37];
    s32 unk_60;
    s16 unk_64;
} S_800247C0_7;   /* var_sp10 in func_800247C0 */

typedef struct S_800247C0_8 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800247C0_8;   /* ((S_800247C0_1 *)temp_s2)->unk_08 in func_800247C0 */



typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} LocalVec;

typedef struct {
    void *sp10;
    s32 unused14;
    LocalVec sp18;
} LocalStack;

s16 func_8002458C();
s32 func_8003DB94();
void *func_8003FC64();
s32 func_8004491C();
s32 func_80069EF8();
s32 func_800A48F0();
extern s32 D_800246B0;
extern s16 D_8002992E;
extern s32 D_80045340;
extern s32 D_800814A0;
extern s32 D_80083460;
extern s32 D_800DE870;
extern s32 D_800E3D7C;

void func_800247C0(void *arg0, void *arg1)
{
    void *var_sp10;
    u16 var_x;
    s32 sp20;
    s16 temp_v0_5;
    s16 temp_v1_3;
    s16 var_s3;
    s32 temp_fp;
    s32 temp_s6;
    s32 temp_v0;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u32 temp_v1;
    u16 temp_v1_2;
    u16 temp_v1_4;
    void *temp_a0;
    void *temp_s0;
    void *temp_s1;
    void *temp_s2;
    u8 *global_base;

    D_8002992E = 1;
    var_x = (func_80069EF8() & 0x3F) - 0x20;
    temp_fp = (func_80069EF8() & 0x3F) - 0x20;
    temp_v0 = func_80069EF8();
    temp_s2 = ((S_800247C0_0 *)arg0)->unk_20;
    temp_a0 = ((S_800247C0_1 *)temp_s2)->unk_08;
    temp_s1 = ((S_800247C0_1 *)temp_s2)->unk_0C;
    ((S_800247C0_2 *)arg1)->unk_00.at00.v = ((S_800247C0_3 *)temp_a0)->unk_00.at00.v;
    ((S_800247C0_2 *)arg1)->unk_04.at00.v = ((S_800247C0_3 *)temp_a0)->unk_04;
    temp_s6 = (temp_v0 & 0x3F) - 0x20;
    ((S_800247C0_2 *)arg1)->unk_08.at00.v = ((S_800247C0_3 *)temp_a0)->unk_08;
    temp_v1 = ((S_800247C0_4 *)temp_s1)->unk_1C.s;
    temp_s2 += 0x20;
    var_sp10 = temp_s2;
    if (temp_v1 >= 0x801U) {
        temp_v0_2 = temp_v1 - 0x50;
        ((S_800247C0_4 *)temp_s1)->unk_1C.s = temp_v0_2;
        if ((u32)(temp_v0_2 & 0xFFFF) < 0x800U) {
            ((S_800247C0_4 *)temp_s1)->unk_1C.s = 0x800U;
        }
    }
    temp_v1_2 = ((S_800247C0_4 *)temp_s1)->unk_1E.s;
    if (temp_v1_2 >= 0x801U) {
        temp_v0_3 = temp_v1_2 - 0x50;
        ((S_800247C0_4 *)temp_s1)->unk_1E.s = temp_v0_3;
        if ((u32)(temp_v0_3 & 0xFFFF) < 0x800U) {
            ((S_800247C0_4 *)temp_s1)->unk_1E.s = 0x800U;
        }
    }
    if (((S_800247C0_0 *)arg0)->unk_28 >= 0xB) {
        var_s3 = 0;
        for (; var_s3 < 4; var_s3++) {
            temp_s2 = func_8003FC64(0x212);
            if (temp_s2 == NULL) {
                continue;
            }
            temp_s0 = temp_s2 + 0x20;
            ((S_800247C0_5 *)temp_s0)->unk_28 = 0x14;
            ((S_800247C0_1 *)temp_s2)->unk_10 = &D_800246B0;
            func_8004491C(temp_s2, &D_80045340);
            temp_s1 = ((S_800247C0_1 *)temp_s2)->unk_0C;
            ((S_800247C0_4 *)temp_s1)->unk_10 = 0x20;
            ((S_800247C0_4 *)temp_s1)->unk_14 |= 0xC;
            temp_a0 = ((S_800247C0_1 *)temp_s2)->unk_08;
            ((S_800247C0_3 *)temp_a0)->unk_00.at02.v =
                ((S_800247C0_2 *)arg1)->unk_00.at02.v + var_x;
            ((S_800247C0_8 *)(((S_800247C0_1 *)temp_s2)->unk_08))->unk_06 =
                ((S_800247C0_2 *)arg1)->unk_04.at02.v + temp_fp;
            ((S_800247C0_8 *)(((S_800247C0_1 *)temp_s2)->unk_08))->unk_0A =
                ((S_800247C0_2 *)arg1)->unk_08.at02.v + temp_s6 - 0x10;
            sp20 = 0 - ((s32)(var_x << 0x10) >> 7);
            ((S_800247C0_5 *)temp_s0)->unk_88 = sp20;
            ((S_800247C0_5 *)temp_s0)->unk_8C =
                0 - ((s32)(temp_fp << 0x10) >> 7);
            ((S_800247C0_5 *)temp_s0)->unk_90 =
                0 - ((s32)(temp_s6 << 0x10) >> 7);
            temp_s1 = ((S_800247C0_1 *)temp_s2)->unk_0C;
            ((S_800247C0_4 *)temp_s1)->unk_1E.u = 0x1000;
            ((S_800247C0_4 *)temp_s1)->unk_1C.u = 0x1000;
            temp_v1_3 = func_8002458C(3);
            ((S_800247C0_4 *)temp_s1)->unk_0E = 0;
            ((S_800247C0_4 *)temp_s1)->unk_0D = 0;
            ((S_800247C0_4 *)temp_s1)->unk_0C = 0;
            if (temp_v1_3 == 0) {
                ((S_800247C0_4 *)temp_s1)->unk_0C = 0x10;
            }
            if (temp_v1_3 == 1) {
                ((S_800247C0_4 *)temp_s1)->unk_0D = 0x10;
            }
            if (temp_v1_3 == 2) {
                ((S_800247C0_4 *)temp_s1)->unk_0E = 0x10;
            }
            ((S_800247C0_4 *)temp_s1)->unk_12 = 0x7DCF;
            ((S_800247C0_4 *)temp_s1)->unk_14 |= 0x100;
            func_8003DB94(temp_s1, &D_800DE870, 0);
        }
    }
    temp_v1_4 = ((S_800247C0_0 *)arg0)->unk_28;
    temp_v0_5 = temp_v1_4 - 1;
    ((S_800247C0_0 *)arg0)->unk_28 = temp_v0_5;
    if ((temp_v0_5 << 0x10) <= 0) {
        global_base = (u8 *)&D_80083460;
        ((S_800247C0_0 *)arg0)->unk_28 = temp_v1_4;
        if (((S_800247C0_6 *)global_base)->unk_10 == NULL) {
            ((S_800247C0_6 *)global_base)->unk_10 = ((S_800247C0_0 *)arg0)->unk_20;
        }
        temp_s2 = ((S_800247C0_0 *)arg0)->unk_20;
        func_800A48F0(temp_s2 + 0x20, 0x18, 0x14);
        ((S_800247C0_7 *)var_sp10)->unk_28 = 0;
        temp_v0 = D_800E3D7C;
        ((S_800247C0_7 *)var_sp10)->unk_64 = -1;
        ((S_800247C0_7 *)var_sp10)->unk_60 = temp_v0;
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
