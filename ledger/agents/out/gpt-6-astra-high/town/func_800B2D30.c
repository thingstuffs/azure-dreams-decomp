#include "common.h"

typedef struct S_800B0490_0 {
    u8 pad_00[0x8];
    union { s32 s; volatile s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B0490_0;   /* state in func_800B0490 */

typedef struct S_800B0490_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B0490_1;   /* arg0 in func_800B0490 */


extern void func_80053DA8();
extern void func_800AE4D4();
extern void func_800AF1B4();
extern void func_800B0424();
extern u8 D_80083160[];


/* Handles menu actions and directional input with held-button repeat. */
void func_800B0490(S_800B0490_1 *menu)
{
    s32 direction;
    s32 move_mode;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 repeat_buttons;
    s32 pressed_buttons;
    u8 *pad_state;

    direction = 0;
    move_mode = direction;
    pad_state = D_80083160;
    held_buttons = ((S_800B0490_0 *)pad_state)->unk_08.s;
    if (held_buttons == 0) {
        goto done;
    }

    pressed_buttons = ((S_800B0490_0 *)pad_state)->unk_10;
    if (pressed_buttons & 0x20) {
        func_80053DA8(0x515, pad_state);
        func_800AE4D4(menu->unk_08);
        goto done;
    }

    if (pressed_buttons & 0x40) {
        func_80053DA8(0x503, pad_state);
        func_800B0424(menu);
        goto done;
    }

    if (!(held_buttons & 0x5000)) {
        goto done;
    }

    if (pressed_buttons & 0x4000) {
        menu->unk_10 = 0;
        move_mode = 4;
        direction = 1;
        goto move;
    }

    if (pressed_buttons & 0x1000) {
        menu->unk_10 = 0;
        move_mode = 4;
        direction = -1;
        goto move;
    }

    repeat_ticks = menu->unk_10;
    if (repeat_ticks >= 5) {
        menu->unk_10 = repeat_ticks - 3;
        repeat_buttons = ((S_800B0490_0 *)pad_state)->unk_08.u;
        if (repeat_buttons & 0x4000) {
            direction = 1;
            move_mode = 4;
            goto move;
        }
        if (repeat_buttons & 0x1000) {
            direction = -1;
            move_mode = 4;
        }
    } else {
        menu->unk_10 = repeat_ticks + 1;
    }

move:
    if (direction == 0) {
        goto done;
    }
    func_80053DA8(0x502, pad_state);
    func_800AF1B4(menu->unk_04, direction, move_mode);

done:
    return;
}
