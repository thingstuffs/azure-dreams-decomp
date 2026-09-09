#include "common.h"

typedef struct S_800B260C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
} S_800B260C_0;   /* base in func_800B260C */

typedef struct S_800B260C_1 {
    u8 pad_00[0x10];
    union { s32 s; volatile s32 u; } unk_10;   /* accessed as both */
} S_800B260C_1;   /* arg0 in func_800B260C */



extern u8 D_80083160[];

extern void SD_Call(s32);
extern void func_800B1DCC(void *);
extern void func_800B1F80(void *, s32);
extern void func_800B2068(void *);
extern void func_800B2394(void *, s32);
extern s32 func_800B2400(void *);
extern void func_800B25D8(void *);
extern void func_800B2CE8(void *);

/* Handles menu button actions and directional cursor movement with key repeat. */
void func_800B260C(u8 *menu) {
    u8 *pad_state = D_80083160;
    s32 held_buttons = ((S_800B260C_0 *)pad_state)->unk_08;
    s32 pressed_buttons;
    s32 cursor_step = 0;
    s32 select_result;
    s32 repeat_ticks;
    s32 held_directions;

    if (held_buttons == 0) {
        goto finish;
    }

    pressed_buttons = ((S_800B260C_0 *)pad_state)->unk_10.s;
    if (pressed_buttons & 0x20) {
        SD_Call(0x515);
        func_800B2CE8(menu - 0x20);
        goto finish;
    }
    if (pressed_buttons & 0x40) {
        select_result = func_800B2400(menu);
        if (select_result == 0) {
            SD_Call(0x503);
            goto update;
        }
        if (select_result != 3) {
            goto finish;
        }
        SD_Call(0x506);
        goto finish;
    }
    if (pressed_buttons & 0x80) {
        SD_Call(0x503);
        goto finish;
    }
    if (pressed_buttons & 0x10) {
        SD_Call(0x503);
        func_800B25D8(menu);
update:
        func_800B2068(menu);
        goto finish;
    }
    if (pressed_buttons & 4) {
        func_800B2394(menu, 0);
        goto finish;
    }
    if (pressed_buttons & 1) {
        func_800B2394(menu, 1);
        goto finish;
    }
    if ((held_buttons & 0xF000) == 0) {
        goto finish;
    }

    if (pressed_buttons & 0xF000) {
        ((S_800B260C_1 *)menu)->unk_10.s = 0;
        pressed_buttons = ((S_800B260C_0 *)pad_state)->unk_10.u;
        if (pressed_buttons & 0x8000) {
            cursor_step = -5;
            goto apply;
        }
        if (pressed_buttons & 0x2000) {
            cursor_step = 5;
            goto apply;
        }
        if (pressed_buttons & 0x1000) {
            cursor_step = -1;
            goto apply;
        }
        if (pressed_buttons & 0x4000) {
            cursor_step = 1;
            goto apply;
        }
    } else {
        repeat_ticks = ((S_800B260C_1 *)menu)->unk_10.s;
        if (repeat_ticks < 5) {
            ((S_800B260C_1 *)menu)->unk_10.s = repeat_ticks + 1;
        } else {
            if (held_buttons & 0x8000) {
                cursor_step = -5;
                goto decrement;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (held_buttons & 0x2000) {
                cursor_step = 5;
                goto decrement;
            }
            held_directions = ((S_800B260C_0 *)pad_state)->unk_08;
            if (held_directions & 0x1000) {
                cursor_step = -1;
                goto decrement;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            if (held_directions & 0x4000) {
                cursor_step = 1;
            }
decrement:
            ((S_800B260C_1 *)menu)->unk_10.u--;
        }
    }

apply:
    if (cursor_step != 0) {
        SD_Call(0x502);
        func_800B1F80(menu, cursor_step);
    }

finish:
    func_800B1DCC(menu);
}
