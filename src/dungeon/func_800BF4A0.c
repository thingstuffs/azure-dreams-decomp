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

/* Fades the color toward the target, then back to neutral, and marks completion. */
void func_800C4C00(void *fade)
{
    u8 *color_state;
    u16 *effect_counts;
    u16 frames_left;

    color_state = (u8 *)&D_80083178;
    if (((S_800C4C00_0 *)fade)->unk_04.s == 0) {
        ((S_800C4C00_1 *)color_state)->unk_90 +=
            (((S_800C4C00_0 *)fade)->unk_00 - ((S_800C4C00_1 *)color_state)->unk_90) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        ((S_800C4C00_1 *)color_state)->unk_91 +=
            (((S_800C4C00_0 *)fade)->unk_01 - ((S_800C4C00_1 *)color_state)->unk_91) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        ((S_800C4C00_1 *)color_state)->unk_92 +=
            (((S_800C4C00_0 *)fade)->unk_02 - ((S_800C4C00_1 *)color_state)->unk_92) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            ((S_800C4C00_0 *)fade)->unk_06.s = 0x10;
            ((S_800C4C00_0 *)fade)->unk_04.u++;
        }
    } else {
        ((S_800C4C00_1 *)color_state)->unk_90 +=
            (0x80 - ((S_800C4C00_1 *)color_state)->unk_90) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        ((S_800C4C00_1 *)color_state)->unk_91 +=
            (0x80 - ((S_800C4C00_1 *)color_state)->unk_91) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        ((S_800C4C00_1 *)color_state)->unk_92 +=
            (0x80 - ((S_800C4C00_1 *)color_state)->unk_92) /
            ((S_800C4C00_0 *)fade)->unk_06.s;
        frames_left = ((S_800C4C00_0 *)fade)->unk_06.u - 1;
        ((S_800C4C00_0 *)fade)->unk_06.u = frames_left;
        if ((s16)frames_left <= 0) {
            ((S_800C4C00_1 *)color_state)->unk_90 = 0x80;
            ((S_800C4C00_1 *)color_state)->unk_91 = 0x80;
            ((S_800C4C00_1 *)color_state)->unk_92 = 0x80;
            effect_counts = (u16 *)&D_80083460;
            effect_counts[5]--;
            (*(u16 *)((u8 *)fade + -2)) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
