#include "common.h"


extern volatile s32 D_801379A8;
extern volatile s32 D_801379B0;

extern s32 func_80058FF0(s32 value, s32 direction, s32 amount);
extern void func_80063FF8(s32 sound);
extern s32 func_804016D0(void);
extern void func_804018FC(void);
extern void func_804067BC(void *object);
extern void func_80406CFC(void *object);
extern void func_804070C4(void *object);
extern void func_804083FC(s32 field20, s32 field24);


typedef struct S_80406DA0_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_80406DA0_0;   /* object in func_80406DA0 */

/* Handles menu selection, held-button repeats, and menu exit. */
void func_80406DA0(void *object)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 direction;
    s32 repeat_ticks;
    s32 repeat_buttons;

    held_buttons = D_801379A8;
    direction = 0;
    if (held_buttons != 0) {
        object = (u8 *)object + 1;
        object = (u8 *)object - 1;
        pressed_buttons = D_801379B0;
        if (pressed_buttons & 0x40) {
            func_80063FF8(0x515);
            goto forced_tail;
        }
        if (pressed_buttons & 0x20) {
            func_80063FF8(0x514);
            func_80406CFC(object);
            goto direction_check;
        }
        if (!(held_buttons & 0x5000)) {
            goto direction_check;
        }
        if (!(pressed_buttons & 0x5000)) {
            goto held_counter;
        }
        (*(s32 *)((u8 *)object + (0x30))) = 0;
        pressed_buttons = D_801379B0;
        if (pressed_buttons & 0x1000) {
            direction = -1;
            goto direction_check;
        }
        if (pressed_buttons & 0x4000) {
            direction = 1;
        }
        goto direction_check;

held_counter:
        repeat_ticks = ((S_80406DA0_0 *)object)->unk_30;
        if (repeat_ticks < 13) {
            goto store_next;
        }
        (*(s32 *)((u8 *)object + (0x30))) = repeat_ticks - 4;
        repeat_buttons = D_801379A8;
        if (repeat_buttons & 0x1000) {
            direction = -1;
            goto direction_check;
        }
        if (repeat_buttons & 0x4000) {
            direction = 1;
        }
        goto direction_check;

store_next:
        ((S_80406DA0_0 *)object)->unk_30 = repeat_ticks + 1;

direction_check:
        if (direction != 0) {
            func_80063FF8(0x502);
            ((S_80406DA0_0 *)object)->unk_2C =
                func_80058FF0(((S_80406DA0_0 *)object)->unk_2C, direction, 5);
            func_804067BC(object);
        }
    }

    direction = func_804016D0();
    func_804018FC();
    if (direction == 0) {
        return;
    }
    if (direction == 1) {
        return;
    }

forced_tail:
    func_804070C4((u8 *)object - 0x20);
    func_804083FC(((S_80406DA0_0 *)object)->unk_20, ((S_80406DA0_0 *)object)->unk_24);
}
