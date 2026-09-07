#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800D3F74_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x68];
    s16 unk_88;
    u8 pad_8A[0x2];
    void * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x6];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
} S_800D3F74_0;   /* result in func_800D3F74 */

typedef struct S_800D3F74_1 {
    u8 pad_00[0x8];
    s8 * unk_08;
    s8 * unk_0C;
    void * unk_10;
} S_800D3F74_1;   /* object in func_800D3F74 */

typedef struct S_800D3F74_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800D3F74_2;   /* part0 in func_800D3F74 */

typedef struct S_800D3F74_3 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800D3F74_3;   /* part1 in func_800D3F74 */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_8003DB94();
extern s8 func_8009FB34();
extern void func_800A2B04();
extern s16 func_800BCB04();
extern void func_80099FDC();
extern void func_8009A21C();

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_800D4158;
extern u8 D_800D4494;
extern u8 D_800DEEC0;

void *func_800D3F74(s16 arg0, u8 arg1, u8 arg2, s16 arg3)
{
    s8 *part0;
    s8 *result = NULL;
    s8 *object;
    register u8 held_arg2 ASM_REG("$20") = arg2;   /* MATCH pin: retail schedule: same instructions, different order without it */
    register u8 held_arg1 ASM_REG("$21") = arg1;   /* MATCH pin: retail schedule: same instructions, different order without it */
    s8 *part1;
    s16 height;
    s32 mode;
    u8 x;
    u8 y;

    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        result = object + 0x20;
        ((S_800D3F74_0 *)result)->unk_13 = 0x34;
        if (arg0 == 1) {
            ((S_800D3F74_0 *)result)->unk_14 |= 0x2000;
            ((S_800D3F74_0 *)result)->unk_1C |= 0x2000;
        }
        func_8004491C(object, &D_80045340);
        part0 = ((S_800D3F74_1 *)object)->unk_08;
        ((S_800D3F74_2 *)part0)->unk_0A = arg3;
        part1 = ((S_800D3F74_1 *)object)->unk_0C;
        ((S_800D3F74_3 *)part1)->unk_0C.at02.v = 0x80;
        ((S_800D3F74_3 *)part1)->unk_0C.at01.v = 0x80;
        ((S_800D3F74_3 *)part1)->unk_0C.at00.v = 0x80;
        ((S_800D3F74_3 *)part1)->unk_1E = 0x1000;
        ((S_800D3F74_3 *)part1)->unk_1C = 0x1000;
        ((S_800D3F74_3 *)part1)->unk_24 = held_arg1;
        ((S_800D3F74_3 *)part1)->unk_25 = held_arg2;
        ((S_800D3F74_3 *)part1)->unk_12 = 0x7E40;
        ((S_800D3F74_3 *)part1)->unk_14 |= 0x100;
        func_8003DB94(part1, &D_800DEEC0, 0);
        ((S_800D3F74_1 *)object)->unk_10 = &D_800D4158;
        ((S_800D3F74_0 *)result)->unk_8C = &D_800D4494;
        ((S_800D3F74_3 *)part1)->unk_26 =
            func_8009FB34(((S_800D3F74_3 *)part1)->unk_24, ((S_800D3F74_3 *)part1)->unk_25);
        func_800A2B04(part0, ((S_800D3F74_3 *)part1)->unk_24,
                     ((S_800D3F74_3 *)part1)->unk_25);
        height = func_800BCB04(((S_800D3F74_2 *)part0)->unk_02,
                               ((S_800D3F74_2 *)part0)->unk_06,
                               ((S_800D3F74_2 *)part0)->unk_0A);
        ((S_800D3F74_0 *)result)->unk_88 = height;
        ((S_800D3F74_0 *)result)->unk_90.at00.v = 0;
        ((S_800D3F74_0 *)result)->unk_90.at02.v = arg3 - height;
        ((S_800D3F74_3 *)part1)->unk_0C.at00u.v = 0x2C808080;
        ((S_800D3F74_3 *)part1)->unk_14 |= 0x8000;
        func_80099FDC(object);
        x = ((S_800D3F74_3 *)part1)->unk_24;
        y = ((S_800D3F74_3 *)part1)->unk_25;
        mode = 0x3000;
        if (((S_800D3F74_0 *)result)->unk_1C & 0x2000) {
            mode = 0x300;
        }
        func_8009A21C(x, y, mode);
        ((S_800D3F74_0 *)result)->unk_9A = 0xE;
        ((S_800D3F74_0 *)result)->unk_9C = -1;
        ((S_800D3F74_0 *)result)->unk_1C |= 0x40000200;
    }
    return result;
}

/* MECHANISM: The true-space function uses a 0x30 frame and fixed s1-s5 object/part/argument roles;
   arg0 and arg3 remain naturally allocated so their temporary computations stay in v0.
   Naming x/y before the mode test hoists both lbu operations and removes the one-word load-delay nop;
   the retail store-slot lineage requires 2.7.2-cdk-G0. */
