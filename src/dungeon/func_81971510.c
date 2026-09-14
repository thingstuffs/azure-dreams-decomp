#include "common.h"
extern u8 D_80020000[];

#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern void *D_80024008[];
extern s16 D_80025FF4;
extern s32 D_800814A0;

/* Advances a timed visual update and sets completion flags when the countdown expires. */
void func_81971510(void *effect, s32 unused, void *visual)
{
    u8 *effect_bytes;
    u16 countdown;
    s32 step_index;
    u8 *status_page;
    u8 *visual_bytes;
    u8 *jump_table;
    u8 *flags_page;
    u16 field_value;
    static void *const case_labels[] = {
        &&case_0, &&case_1, &&case_2, &&case_3,
        &&case_4, &&case_default
    };

    effect_bytes = (u8 *)effect;
    visual_bytes = (u8 *)visual;
#ifdef NON_MATCHING
    status_page = (u8 *)&D_80025FF4 - 0x5FF4;
#else
    status_page = (u8 *)D_80020000;
#endif
    countdown = U16_AT(effect_bytes, 0x38);
    *(s16 *)(status_page + 0x5FF4) = 1;
    countdown--;
    U16_AT(effect_bytes, 0x38) = countdown;
    step_index = (u32)(s16)countdown;
    if ((u32)step_index >= 20U) {
        goto case_default;
    }
    jump_table = (u8 *)D_80024008;
    (void)case_labels;
    goto *((void **)jump_table)[(u32)step_index];

case_0:
    field_value = 0x20;
    goto set_shade;
case_1:
    field_value = 0x35;
    goto set_shade;
case_2:
    field_value = 0x50;
    goto set_shade;
case_3:
    field_value = 0x65;
    goto set_shade;
case_4:
    field_value = 0x80;
set_shade:
    U8_AT(visual_bytes, 0x0E) = field_value;
    U8_AT(visual_bytes, 0x0D) = field_value;
    U8_AT(visual_bytes, 0x0C) = field_value;

case_default:
    field_value = U16_AT(visual_bytes, 0x1A) + 400;
    U16_AT(visual_bytes, 0x1A) = field_value;
    if (S16_AT(effect_bytes, 0x38) > 0) {
        return;
    }
#ifdef NON_MATCHING
    flags_page = (u8 *)&D_800814A0 - 0x14A0;
#else
    flags_page = (u8 *)0x80080000;
#endif
    field_value = U16_AT((u8 *)effect_bytes - 2, 0) | 0x8000;
    U16_AT((u8 *)effect_bytes - 2, 0) = field_value;
    *(u32 *)(flags_page + 0x14A0) |= 0x8000;
}
