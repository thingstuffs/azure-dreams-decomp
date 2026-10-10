#include "common.h"
#include "shared/object_flags.h"


#define U16_AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define S16_AT(p, off) (*(s16 *)((u8 *)(p) + (off)))
#define U8_AT(p, off) (*(u8 *)((u8 *)(p) + (off)))


/* Advances a timed visual update and sets completion flags when the countdown expires. */
void func_80024D10(void *effect, s32 unused, void *visual)
{
    u8 *effect_bytes;
    u16 countdown;
    s32 step_index;
    u8 *status_page;
    u8 *visual_bytes;
    u8 *flags_page;
    u16 field_value;

    effect_bytes = (u8 *)effect;
    visual_bytes = (u8 *)visual;
    status_page = (u8 *)&D_80025FF4 - 0x5FF4;
    countdown = U16_AT(effect_bytes, 0x38);
    *(s16 *)(status_page + 0x5FF4) = 1;
    countdown--;
    U16_AT(effect_bytes, 0x38) = countdown;
    step_index = (u32)(s16)countdown;
    if ((u32)step_index < 20U) {
        switch (step_index) {
        case 0: case 9: case 10: case 19:
            field_value = 0x20;
            break;
        case 1: case 8: case 11: case 18:
            field_value = 0x35;
            break;
        case 2: case 7: case 12: case 17:
            field_value = 0x50;
            break;
        case 3: case 6: case 13: case 16:
            field_value = 0x65;
            break;
        case 4: case 5: case 14: case 15:
            field_value = 0x80;
            break;
        }
        U8_AT(visual_bytes, 0x0E) = field_value;
        U8_AT(visual_bytes, 0x0D) = field_value;
        U8_AT(visual_bytes, 0x0C) = field_value;
    }
    field_value = U16_AT(visual_bytes, 0x1A) + 400;
    U16_AT(visual_bytes, 0x1A) = field_value;
    if (S16_AT(effect_bytes, 0x38) > 0) {
        return;
    }
    flags_page = (u8 *)0x80080000;
    field_value = U16_AT((u8 *)effect_bytes - 2, 0) | 0x8000;
    U16_AT((u8 *)effect_bytes - 2, 0) = field_value;
    *(u32 *)(flags_page + 0x14A0) |= 0x8000;
}


