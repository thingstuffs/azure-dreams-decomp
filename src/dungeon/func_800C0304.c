#include "common.h"

typedef struct S_800C5A64_0 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_800C5A64_0;   /* arg2 in func_800C5A64 */

typedef struct S_800C5A64_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    u8 pad_0E[0x2];
    union { s16 s; u16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0xA];
    s16 unk_1C;
} S_800C5A64_1;   /* arg0 in func_800C5A64 */

typedef struct S_800C5A64_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C5A64_2;   /* counter_base in func_800C5A64 */



extern void func_800478B8(void *);
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800C5A64(void *arg0, s32 *arg1, void *arg2)
{
    s16 remaining;
    u8 *counter_base;

    arg1[0] += arg1[3];
    arg1[1] += arg1[4];
    arg1[2] += arg1[5];
    arg1[3] -= arg1[3] >> 3;
    arg1[4] -= arg1[4] >> 3;

    func_800478B8(arg2);

    ((S_800C5A64_0 *)arg2)->unk_0C -= ((S_800C5A64_0 *)arg2)->unk_0C / ((S_800C5A64_1 *)arg0)->unk_10.s;
    ((S_800C5A64_0 *)arg2)->unk_0D -= ((S_800C5A64_0 *)arg2)->unk_0D / ((S_800C5A64_1 *)arg0)->unk_10.s;
    ((S_800C5A64_0 *)arg2)->unk_0E -= ((S_800C5A64_0 *)arg2)->unk_0E / ((S_800C5A64_1 *)arg0)->unk_10.s;

    remaining = ((S_800C5A64_1 *)arg0)->unk_10.u - 1;
    ((S_800C5A64_1 *)arg0)->unk_10.s = remaining;
    if ((remaining << 16) <= 0) {
        if ((((S_800C5A64_1 *)arg0)->unk_0C == 0) &&
            (((S_800C5A64_1 *)arg0)->unk_1C == 0)) {
            counter_base = (u8 *)&D_80083460;
            ((S_800C5A64_2 *)counter_base)->unk_0A--;
        }
        (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: The two call-crossing arguments naturally occupy s1/s0, producing
   the retail 0x20 frame and save order; the one-argument callee contract leaves
   the final arg1[4] store available for the jal delay slot. */
