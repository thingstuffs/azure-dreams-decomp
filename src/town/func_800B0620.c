#include "common.h"

extern s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
extern void SD_Call(s32 arg0);
extern void func_800ADB30(void *arg0);
extern void close_twin_shop(void *arg0);
extern void func_800B1778(s32 arg0, s32 arg1, s32 arg2);
extern void func_800B17C0(s32 arg0, s32 arg1);
extern s32 D_80082AB8;
extern s32 D_80083160[5];

/* Handles grid menu navigation, confirmation, and cancellation. */
void func_800ADD80(s32 *menu) {
    s32 *pad_state;
    s32 held_buttons;
    s32 pressed_buttons;
    s32 selection_step;
    s32 repeat_ticks;
    s32 selection;
    s32 row;
    u8 *selected_entry;
    pad_state = D_80083160;
    held_buttons = pad_state[2];
    selection_step = 0;
    if (held_buttons == 0) return;
    if (menu[2] == 0) {
        if (pad_state[4] & 0x20) {
            SD_Call(0x515);
            D_80082AB8 = 0;
            close_twin_shop((u8 *)menu - 0x20);
        }
        return;
    }
    pressed_buttons = pad_state[4];
    if (pressed_buttons & 0x20) {
        SD_Call(0x515);
        D_80082AB8 = 0;
        close_twin_shop((u8 *)menu - 0x20);
        return;
    }
    if (pressed_buttons & 0x40) {
        SD_Call(0x514);
        D_80082AB8 = 1;
        close_twin_shop((u8 *)menu - 0x20);
        selected_entry = (u8 *)(menu[1] * 4 + menu[8]);
        selected_entry[3] |= 0x20;
        return;
    }
    if (!(held_buttons & 0xF000)) return;
    if (pad_state[4] & 0xF000) {
        *(volatile s32 *)&menu[5] = 0;
        pressed_buttons = *(volatile s32 *)&pad_state[4];
        if (pressed_buttons & 0x8000) selection_step = -5;
        else if (pressed_buttons & 0x2000) selection_step = 5;
        else if (pressed_buttons & 0x1000) selection_step = -1;
        else if (pressed_buttons & 0x4000) selection_step = 1;
    } else {
        if (menu[5] >= 9) {
            if (held_buttons & 0x8000) selection_step = -5;
            else if (held_buttons & 0x2000) selection_step = 5;
            else if (held_buttons & 0x1000) selection_step = -1;
            else if (held_buttons & 0x4000) selection_step = 1;
            repeat_ticks = *(volatile s32 *)&menu[5];
            menu[5] = repeat_ticks - 1;
        } else {
            menu[5]++;
            return;
        }
    }
    selection = func_80049E1C(menu[1], selection_step, menu[2]);
    row = selection / 5;
    if (selection == menu[1]) return;
    SD_Call(0x502);
    menu[1] = selection;
    if (row != menu[3]) {
        menu[3] = row;
        func_800B1778(menu[10], row, selection);
    }
    func_800B17C0(menu[10], selection);
    func_800ADB30(menu);
}
