#include "common.h"


typedef struct EffectColor {
    u8 pad[0xC];
    u8 red;
    u8 green;
    u8 blue;
} EffectColor;

extern u16 D_800257CE[5];
extern s16 D_800257CC[5];
extern s32 D_800814A0;

extern void func_8002491C(void) __attribute__((noreturn));
void func_80024A98(void *);


typedef struct S_81880F28_0 {
    void * unk_00;
    u8 pad_04[0x6];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x10];
    u16 unk_1C;
} S_81880F28_0;   /* arg0 in func_81880F28 */

typedef struct S_81880F28_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81880F28_1;   /* object in func_81880F28 */

typedef struct S_81880F28_2 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_81880F28_2;   /* motion in func_81880F28 */

typedef struct S_81880F28_3_pre {
    EffectColor * unk_00;
    u8 pad_04[0x10];
} S_81880F28_3_pre;   /* the 0x14 bytes before ((S_81880F28_0 *)arg0)->unk_00 in func_81880F28, addressed as ((S_81880F28_0 *)arg0)->unk_00[-1] */

/* Tint the object red, restore its color, and advance its motion. */
void func_81880F28(void *effect, void *motion_data) {
    void *motion = motion_data;
    void *object;
    EffectColor *color;
    s16 state;
    s32 channel_value;

    D_800257CE[0]++;
    state = ((S_81880F28_0 *)effect)->unk_0A.s;

    if (state == 1) {
        goto redden_color;
    }
    if (state >= 2) {
        goto check_restore;
    }
    if (state == 0) {
        goto init_effect;
    }
    func_8002491C();
    return;

check_restore:
    if (state == 2) {
        goto restore_color;
    }
    func_8002491C();
    return;

init_effect:
    object = ((S_81880F28_0 *)effect)->unk_00;
    ((S_81880F28_1 *)object)->unk_1C |= 0x10000000;
    ((S_81880F28_0 *)effect)->unk_0A.u++;

redden_color:
    color = ((S_81880F28_3_pre *)(((S_81880F28_0 *)effect)->unk_00))[-1].unk_00;

    channel_value = color->red + 1;
    color->red = channel_value;
    if ((u32)(channel_value & 0xFF) >= 0xC1U) {
        color->red = 0xC0;
    }

    channel_value = color->green - 1;
    color->green = channel_value;
    if ((u32)(channel_value & 0xFF) < 0x40U) {
        color->green = 0x40;
    }

    channel_value = color->blue - 1;
    color->blue = channel_value;
    if ((u32)(channel_value & 0xFF) < 0x40U) {
        color->blue = 0x40;
    }

    if (D_800257CC[0] >= 14) {
        goto update_motion;
    }

    ((S_81880F28_0 *)effect)->unk_0A.u++;
    func_8002491C();
    return;

restore_color:
    color = ((S_81880F28_3_pre *)(((S_81880F28_0 *)effect)->unk_00))[-1].unk_00;

    channel_value = color->red - 4;
    color->red = channel_value;
    if ((u32)(channel_value & 0xFF) < 0x80U) {
        color->red = 0x80;
    }

    channel_value = color->green + 4;
    color->green = channel_value;
    if ((u32)(channel_value & 0xFF) >= 0x81U) {
        color->green = 0x80;
    }

    channel_value = color->blue + 4;
    color->blue = channel_value;
    if ((u32)(channel_value & 0xFF) >= 0x81U) {
        color->blue = 0x80;
    }

    if (D_800257CC[0] == 0) {
        ((S_81880F28_1 *)((S_81880F28_0 *)effect)->unk_00)->unk_1C &= ~0x10000000;
        (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }

update_motion:
    ((S_81880F28_2 *)motion)->unk_08 += ((S_81880F28_2 *)motion)->unk_14;
    ((S_81880F28_2 *)motion)->unk_14 += -0x80000;
    func_80024A98(motion);
    ((S_81880F28_0 *)effect)->unk_1C++;
}
