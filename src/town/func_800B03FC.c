#include "common.h"

extern s32 func_80049E1C(s32 arg0, s32 arg1, s32 arg2);
extern void SD_Call(s32 arg0);
extern void func_800AD8CC(s32 *arg0);
extern void func_800ADA1C(s32 *arg0);
extern void func_800ADB04(s32 *arg0);
extern void close_twin_shop(void *arg0);
extern void func_800B1778(s32 arg0, s32 arg1, s32 arg2);
extern void func_800B17C0(s32 arg0, s32 arg1);

extern s32 D_80082AB8;
extern s32 D_80083160[5];

/* Handles twin shop input and updates the selected item and row. */
void func_800ADB5C(s32 *menu) {
    s32 *pad_state;
    s32 held_buttons;
    s32 selection_step;
    s32 selection;
    s32 row;

    pad_state = D_80083160;
    held_buttons = pad_state[2];
    selection_step = 0;
    if (held_buttons == 0) {
        return;
    }

    if (pad_state[4] & 0x10) {
        SD_Call(0x514);
        func_800AD8CC(menu);
        goto close_shop;
    }
    if (pad_state[4] & 0x20) {
        SD_Call(0x515);
        D_80082AB8 = 0;
close_shop:
        close_twin_shop((s8 *)menu - 0x20);
        return;
    }
    if (pad_state[4] & 0x40) {
        func_800ADA1C(menu);
        return;
    }
    if (!(held_buttons & 0xF000)) {
        return;
    }

    if (pad_state[4] & 0xF000) {
        menu[5] = 0;
        if (pad_state[4] & 0x8000) selection_step = -5;
        else if (pad_state[4] & 0x2000) selection_step = 5;
        else if (pad_state[4] & 0x1000) selection_step = -1;
        else if (pad_state[4] & 0x4000) selection_step = 1;
    } else {
        if (menu[5] >= 9) {
            if (held_buttons & 0x8000) selection_step = -5;
            else if (held_buttons & 0x2000) selection_step = 5;
            else if (held_buttons & 0x1000) selection_step = -1;
            else if (held_buttons & 0x4000) selection_step = 1;
            menu[5] = *(volatile s32 *)&menu[5] - 1;
        } else {
            menu[5]++;
            return;
        }
    }

    selection = func_80049E1C(menu[1], selection_step, menu[2]);
    row = selection / 5;
    if (selection == menu[1]) {
        return;
    }

    SD_Call(0x502);
    menu[1] = selection;
    if (row != menu[3]) {
        menu[3] = row;
        func_800B1778(menu[10], row, selection);
    }
    func_800B17C0(menu[10], selection);
    if (pad_state[2] & 0x40) {
        func_800ADA1C(menu);
    }
    func_800ADB04(menu);
}
