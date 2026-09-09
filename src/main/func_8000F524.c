#include "common.h"

typedef struct S_80022524_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xC];
    s32 * unk_20;
} S_80022524_0;   /* arg0 in func_80022524 */



extern void SD_Call(s32 code);
extern s32 func_800231E4(s32 mode);
extern s32 func_80049E1C(s32 current, s32 direction, u8 entry);
extern void func_80022488(void *arg0);
extern s32 D_80083160[];
extern u8 D_800280B4[];

/* Handles menu exit buttons and repeated left/right selection changes. */
void func_80022524(S_80022524_0 *menu)
{
    s32 direction;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_delay;
    s32 right_pressed;
    s32 next_delay;
    volatile s32 *input;

    input = D_80083160;
    direction = 0;
    held_buttons = input[2];
    if (held_buttons == 0) {
        return;
    }
    pressed_buttons = input[4];
    if (pressed_buttons & 0x20) {
        s32 *exit_status;

        SD_Call(0x515);
        func_800231E4(1);
        exit_status = menu->unk_20;
        if (exit_status != 0) {
            *exit_status = 1;
        }
        goto common;
    }
    if (pressed_buttons & 0x40) {
        s32 *exit_status;
        s32 *updated_status;
        s32 exit_result;

        SD_Call(0x514);
        exit_status = menu->unk_20;
        if (exit_status != 0) {
            exit_result = func_800231E4(1);
            updated_status = menu->unk_20;
            *updated_status = exit_result;
            goto common;
        }
        func_800231E4(1);
        goto common;
    }
    if ((held_buttons & 0xA000) != 0 && (pressed_buttons & 0xA000) != 0) {
        menu->unk_10 = 0;
        pressed_buttons = input[4];
        if (pressed_buttons & 0x8000) {
            goto negative_tail;
        }
        right_pressed = pressed_buttons & 0x2000;
        goto side_check;
    }
    if (held_buttons & 0xA000) {
        repeat_delay = menu->unk_10;
        if (repeat_delay < 3) {
            next_delay = repeat_delay + 1;
            goto store_counter;
        }
        if (held_buttons & 0x8000) {
            goto negative_tail;
        }
        right_pressed = held_buttons & 0x2000;
        goto side_check;
    }
    goto common;

negative_tail:
    direction = -1;
    goto common;

side_check:
    if (right_pressed == 0) {
        goto common;
    }
    direction = 1;
    goto common;

store_counter:
    menu->unk_10 = next_delay;

common:
    if (direction != 0) {
        s32 new_selection;

        new_selection = func_80049E1C(
            menu->unk_00,
            direction,
            D_800280B4[menu->unk_08 * 0x18 + 0x14]);
        if (new_selection != menu->unk_00) {
            menu->unk_00 = new_selection;
            SD_Call(0x502);
        }
        func_80022488(menu);
    }
}
