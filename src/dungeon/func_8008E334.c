#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u16 D_80082E94;
extern s32 D_800814A0[3];
extern M2C_UNK D_800DD140;
extern void func_80048AC8(void *, s32);

/* Updates an object's scale and brightness through its transition modes. */
void func_80093A94(void *object_data, void *unused, void *state_data) {
    u8 *obj = (u8 *)object_data;
    u8 *state = (u8 *)state_data;
    s16 mode;
    u16 grow_ticks;
    u16 shrink_ticks;
    u16 grow_scale;
    u16 scale_or_ticks;
    u16 mode_next;
    u8 dimmed_brightness;
    u8 brightness;

    func_80048AC8(state, *(s16 *)(obj + 8) + 2);
    if (D_80082E94 & 1) {
        *(u16 *)(state + 0x14) |= 1;
    } else {
        *(u16 *)(state + 0x14) &= 0xFFFE;
    }
    mode = *(s16 *)(obj + 4);
    if (mode == 1) {
        goto mode_one;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto mode_zero;
        }
        goto epilogue;
    }
    if (mode == 2) {
        goto mode_two;
    }
    if (mode == 3) {
        goto set_high;
    }
    goto epilogue;

mode_zero:
    grow_scale = *(u16 *)(state + 0x1C);
    *(u16 *)(state + 0x1C) = (u16)(grow_scale + ((s32)(0x1000 - grow_scale) / 4));
    grow_ticks = *(u16 *)(obj + 6) - 1;
    *(u16 *)(obj + 6) = grow_ticks;
    if ((grow_ticks << 0x10) <= 0) {
        *(u16 *)(state + 0x1C) = 0x1000;
        goto increment_mode;
    }
    goto epilogue;

mode_one:
    if (*(s16 *)(obj + 8) == 0) {
        brightness = *(u8 *)(state + 0xC);
        if (brightness >= 0x81U) {
            dimmed_brightness = brightness - 8;
            *(u8 *)(state + 0xC) = dimmed_brightness;
            *(u8 *)(state + 0xE) = dimmed_brightness;
            *(u8 *)(state + 0xD) = dimmed_brightness;
        }
    }
    if (*(s32 *)(*(u8 **)obj + 0x2C) != (s32)&D_800DD140) {
        goto epilogue;
    }
    if (*(s16 *)(obj + 8) == 0) {
        scale_or_ticks = 8;
        mode_next = *(u16 *)(obj + 4);
        *(u16 *)(obj + 6) = scale_or_ticks;
        goto increment_tail;
    }
    goto set_high;

mode_two:
    scale_or_ticks = *(u16 *)(state + 0x1C);
    *(u16 *)(state + 0x1C) = (u16)(scale_or_ticks + ((s32)(0 - scale_or_ticks) / 4));
    shrink_ticks = *(u16 *)(obj + 6) - 1;
    *(u16 *)(obj + 6) = shrink_ticks;
    if ((shrink_ticks << 0x10) <= 0) {
        *(u16 *)(state + 0x1C) = 0;
        goto increment_mode;
    }
    goto epilogue;

increment_mode:
    mode_next = *(u16 *)(obj + 4);
increment_tail:
    mode_next += 1;
    *(u16 *)(obj + 4) = mode_next;
    goto epilogue;
set_high:
    *(u16 *)(obj - 2) |= 0x8000;
    D_800814A0[0] = D_800814A0[0] | 0x8000;
epilogue:
    return;
}
