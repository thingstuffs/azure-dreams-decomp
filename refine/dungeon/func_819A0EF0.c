#include "common.h"

typedef struct S_800246F0_0_pre {
    u16 unk_00;
} S_800246F0_0_pre;   /* the 0x2 bytes before arg0 in func_800246F0, addressed as arg0[-1] */

typedef struct S_800246F0_0 {
    u8 pad_00[0x3A];
    union { u16 s; s16 u; } unk_3A;   /* accessed as both */
    s16 unk_3C;
} S_800246F0_0;   /* arg0 in func_800246F0 */

typedef struct S_800246F0_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800246F0_1;   /* arg2 in func_800246F0 */

typedef struct S_800246F0_2 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_800246F0_2;   /* arg1 in func_800246F0 */

typedef struct S_800246F0_3 {
    s32 unk_00;
} S_800246F0_3;   /* D_800814A0 in func_800246F0 */


extern void func_800478B8(void *);
extern s16 D_800261B0[8];
extern u8 D_800814A0[];


/* Fade and move the effect, marking it finished when its countdown expires. */
void func_800246F0(void *effect, S_800246F0_2 *motion, S_800246F0_1 *primitive)
{
    s32 brightness;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 ticks_left;

    ticks_left = ((S_800246F0_0 *)effect)->unk_3A.s;
    D_800261B0[0] = 1;
    ((S_800246F0_0 *)effect)->unk_3A.s = ticks_left - 1;
    func_800478B8(primitive);
    brightness = ((s16)((S_800246F0_0 *)effect)->unk_3A.s << 7) /
            ((S_800246F0_0 *)effect)->unk_3C;
    primitive->unk_0E = brightness;
    primitive->unk_0D = brightness;
    primitive->unk_0C = brightness;
    x = motion->unk_00;
    dx = motion->unk_0C;
    y = motion->unk_04;
    dy = motion->unk_10;
    motion->unk_00 = x + dx;
    motion->unk_04 = y + dy;
    if (((S_800246F0_0 *)effect)->unk_3A.u <= 0) {
        ((S_800246F0_0_pre *)effect)[-1].unk_00 |= 0x8000;
        ((S_800246F0_3 *)D_800814A0)->unk_00 |= 0x8000;
    }
}
