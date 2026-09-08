#include "common.h"

typedef struct S_80170920_0 {
    u8 pad_00[0x1C];
    union { s16 s; u16 u; } unk_1C;   /* accessed as both */
    u8 pad_1E[0x6];
    union { u16 s; s16 u; } unk_24;   /* accessed as both */
    s16 unk_26;
} S_80170920_0;   /* arg0 in func_80170920 */

typedef struct S_80170920_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x8];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80170920_1;   /* arg2 in func_80170920 */



extern s32 D_800814A0;

/* Expands and brightens the effect, then shrinks and fades it until expiration. */
void func_80170920(void *effect, void *unused, void *visual)
{
    s16 state;
    s32 fade_brightness;
    u8 brightness;

    state = ((S_80170920_0 *)effect)->unk_1C.s;
    if (state == 1) {
        goto begin_fade;
    }
    if (state >= 2) {
        goto check_fade;
    }
    if (state == 0) {
        goto expand;
    }
    goto update;

check_fade:
    if (state == 2) {
        goto fade;
    }
    goto update;

expand:
    ((S_80170920_1 *)visual)->unk_1C += 0x258;
    ((S_80170920_1 *)visual)->unk_1E += 0x258;
    brightness = ((S_80170920_1 *)visual)->unk_0E + 0xC;
    ((S_80170920_1 *)visual)->unk_0E = brightness;
    ((S_80170920_1 *)visual)->unk_0D = brightness;
    ((S_80170920_1 *)visual)->unk_0C = brightness;
    if (((S_80170920_1 *)visual)->unk_1C < 0x1770) {
        goto update;
    }
    goto advance_state;

begin_fade:
    ((S_80170920_1 *)visual)->unk_10 = 0x20;
    ((S_80170920_1 *)visual)->unk_0E = 0x50;
    ((S_80170920_1 *)visual)->unk_0D = 0x50;
    ((S_80170920_1 *)visual)->unk_0C = 0x50;

advance_state:
    ((S_80170920_0 *)effect)->unk_1C.u++;
    goto update;

fade:
    ((S_80170920_1 *)visual)->unk_10 = 0x60;
    ((S_80170920_0 *)effect)->unk_24.s--;
    ((S_80170920_1 *)visual)->unk_1C -= 0x190;
    ((S_80170920_1 *)visual)->unk_1E -= 0x190;
    fade_brightness = (((S_80170920_0 *)effect)->unk_24.u << 7) /
               ((S_80170920_0 *)effect)->unk_26;
    ((S_80170920_1 *)visual)->unk_0E = fade_brightness;
    ((S_80170920_1 *)visual)->unk_0D = fade_brightness;
    ((S_80170920_1 *)visual)->unk_0C = fade_brightness;

update:
    ((S_80170920_1 *)visual)->unk_1A += 0x190;
    if (((S_80170920_0 *)effect)->unk_24.u <= 0) {
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
