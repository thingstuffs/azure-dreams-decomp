#include "common.h"

typedef struct S_800C4C00_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x1];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800C4C00_0;   /* arg0 in func_800C4C00 */

typedef struct S_800C4C00_1 {
    u8 pad_00[0x90];
    u8 unk_90;
    u8 unk_91;
    u8 unk_92;
} S_800C4C00_1;   /* state in func_800C4C00 */



extern struct S_80083178 D_80083178;
extern s32 D_800814A0;
extern s32 D_80083460;

void func_800C4C00(void *arg0)
{
    u8 *state;
    u16 *counter;
    u16 left;

    state = (u8 *)&D_80083178;
    if (((S_800C4C00_0 *)arg0)->unk_04.s == 0) {
        ((S_800C4C00_1 *)state)->unk_90 +=
            (((S_800C4C00_0 *)arg0)->unk_00 - ((S_800C4C00_1 *)state)->unk_90) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        ((S_800C4C00_1 *)state)->unk_91 +=
            (((S_800C4C00_0 *)arg0)->unk_01 - ((S_800C4C00_1 *)state)->unk_91) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        ((S_800C4C00_1 *)state)->unk_92 +=
            (((S_800C4C00_0 *)arg0)->unk_02 - ((S_800C4C00_1 *)state)->unk_92) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        left = ((S_800C4C00_0 *)arg0)->unk_06.u - 1;
        ((S_800C4C00_0 *)arg0)->unk_06.u = left;
        if ((s16)left <= 0) {
            ((S_800C4C00_0 *)arg0)->unk_06.s = 0x10;
            ((S_800C4C00_0 *)arg0)->unk_04.u++;
        }
    } else {
        ((S_800C4C00_1 *)state)->unk_90 +=
            (0x80 - ((S_800C4C00_1 *)state)->unk_90) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        ((S_800C4C00_1 *)state)->unk_91 +=
            (0x80 - ((S_800C4C00_1 *)state)->unk_91) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        ((S_800C4C00_1 *)state)->unk_92 +=
            (0x80 - ((S_800C4C00_1 *)state)->unk_92) /
            ((S_800C4C00_0 *)arg0)->unk_06.s;
        left = ((S_800C4C00_0 *)arg0)->unk_06.u - 1;
        ((S_800C4C00_0 *)arg0)->unk_06.u = left;
        if ((s16)left <= 0) {
            ((S_800C4C00_1 *)state)->unk_90 = 0x80;
            ((S_800C4C00_1 *)state)->unk_91 = 0x80;
            ((S_800C4C00_1 *)state)->unk_92 = 0x80;
            counter = (u16 *)&D_80083460;
            counter[5]--;
            (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}

/* MECHANISM: Retail is a frameless leaf; the input and one D_80083178 base stay live
   across both CFG arms. The +0x90 color bytes use one held struct base, while the
   counter uses symbolic base indexing to preserve its separate lui/addiu pair; the
   final two flags remain direct halfword/word read-modify-writes. */
