#include "common.h"
#include "shared/game_work.h"

typedef struct S_800B260C_1 {
    u8 pad_00[0x10];
    union { s32 s; s32 u; } unk_10;   /* accessed as both */
} S_800B260C_1;   /* arg0 in func_800B260C */


extern void SD_Call(s32);
extern void func_800B1DCC(void *);
extern void func_800B1F80(s8 *state, s32 input);
extern void func_800B2068(void *);
extern void func_800B2394(void *, s32);
extern s32 func_800B2400(void *);
extern void func_800B25D8(void *);
extern void func_800B2CE8(void *);

/* Handles menu button actions and directional cursor movement with key repeat. */
void func_800B260C(u8 *menu) {
    GameWork *pad_state = &gameWork;
    s32 held_buttons = pad_state->buttons;
    s32 pressed_buttons;
    s32 cursor_step = 0;
    s32 select_result;
    s32 repeat_ticks;
    s32 held_directions;

    if (held_buttons != 0) {
        pressed_buttons = ((s32)pad_state->unk_010);
        if (pressed_buttons & 0x20) {
            SD_Call(0x515);
            func_800B2CE8(menu - 0x20);
        } else if (pressed_buttons & 0x40) {
            select_result = func_800B2400(menu);
            if (select_result == 0) {
                SD_Call(0x503);
                func_800B2068(menu);
            } else if (select_result == 3) {
                SD_Call(0x506);
            }
        } else if (pressed_buttons & 0x80) {
            SD_Call(0x503);
        } else if (pressed_buttons & 0x10) {
            SD_Call(0x503);
            func_800B25D8(menu);
            func_800B2068(menu);
        } else if (pressed_buttons & 4) {
            func_800B2394(menu, 0);
        } else if (pressed_buttons & 1) {
            func_800B2394(menu, 1);
        } else if ((held_buttons & 0xF000) != 0) {
            if (pressed_buttons & 0xF000) {
                ((S_800B260C_1 *)menu)->unk_10.s = 0;
                pressed_buttons = ((s32)pad_state->unk_010);
                if (pressed_buttons & 0x8000) {
                    cursor_step = -5;
                } else if (pressed_buttons & 0x2000) {
                    cursor_step = 5;
                } else if (pressed_buttons & 0x1000) {
                    cursor_step = -1;
                } else if (pressed_buttons & 0x4000) {
                    cursor_step = 1;
                }
            } else {
                repeat_ticks = ((S_800B260C_1 *)menu)->unk_10.s;
                if (repeat_ticks >= 5) {
                    if (held_buttons & 0x8000) {
                        cursor_step = -5;
                    } else if (held_buttons & 0x2000) {
                        cursor_step = 5;
                    } else {
                        held_directions = pad_state->buttons;
                        if (held_directions & 0x1000) {
                            cursor_step = -1;
                        } else if (held_directions & 0x4000) {
                            cursor_step = 1;
                        }
                    }
                    ((S_800B260C_1 *)menu)->unk_10.u--;
                } else {
                    ((S_800B260C_1 *)menu)->unk_10.s = repeat_ticks + 1;
                }
            }
            if (cursor_step != 0) {
                SD_Call(0x502);
                func_800B1F80(menu, cursor_step);
            }
        }
    }

    func_800B1DCC(menu);
}
