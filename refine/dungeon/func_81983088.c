#include "common.h"

typedef struct S_80024888_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024888_0;   /* arg1 in func_80024888 */

typedef struct S_80024888_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024888_1;   /* arg2 in func_80024888 */

typedef struct S_80024888_2_pre {
    u16 unk_00;
} S_80024888_2_pre;   /* the 0x2 bytes before arg0 in func_80024888, addressed as arg0[-1] */

typedef struct S_80024888_2 {
    u8 pad_00[0x30];
    u16 unk_30;
} S_80024888_2;   /* arg0 in func_80024888 */


extern u16 D_800269F8[];
extern s32 D_800814A0[];


/* Advance effect motion, fade its color, and flag it when its lifetime expires. */
void func_80024888(void *effect, S_80024888_0 *motion, S_80024888_1 *color) {
    s32 velocity_x;
    s32 velocity_y;
    u16 update_count;
    u8 brightness;
    u8 faded_brightness;
    u16 life_left;

    update_count = D_800269F8[0];
    velocity_x = motion->unk_0C;
    velocity_y = motion->unk_10;
    D_800269F8[0] = update_count + 1;
    motion->unk_00 = motion->unk_00 + velocity_x;
    motion->unk_04 = motion->unk_04 + velocity_y;
    motion->unk_08 = motion->unk_08 + motion->unk_14;
    motion->unk_14 = motion->unk_14 + 0x2000;
    brightness = color->unk_0C;
    faded_brightness = brightness - (brightness >> 4);
    color->unk_0C = faded_brightness;
    color->unk_0D = faded_brightness;
    color->unk_0E = faded_brightness;
    life_left = ((S_80024888_2 *)effect)->unk_30 - 1;
    ((S_80024888_2 *)effect)->unk_30 = life_left;
    if ((life_left << 0x10) <= 0) {
        ((S_80024888_2_pre *)effect)[-1].unk_00 = ((S_80024888_2_pre *)effect)[-1].unk_00 | 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
