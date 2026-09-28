#include "common.h"
#include "shared/game_work.h"

typedef struct S_800B0490_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B0490_1;   /* arg0 in func_800B0490 */


extern void SD_Call();
extern void func_800AE4D4();
extern void func_800AF1B4();
extern void func_800B0424();


/* Handles menu actions and directional input with held-button repeat. */
void func_800B0490(S_800B0490_1 *menu)
{
    s32 direction;
    s32 move_mode;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 repeat_buttons;
    s32 pressed_buttons;
    GameWork *pad_state;

    direction = 0;
    move_mode = direction;
    pad_state = &gameWork;
    held_buttons = pad_state->buttons;
    if (held_buttons == 0) {
        goto done;
    }

    pressed_buttons = ((s32)pad_state->unk_010);
    if (pressed_buttons & 0x20) {
        SD_Call(0x515, pad_state);
        func_800AE4D4(menu->unk_08);
        goto done;
    }

    if (pressed_buttons & 0x40) {
        SD_Call(0x503, pad_state);
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
        repeat_buttons = pad_state->buttons;
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
    SD_Call(0x502, pad_state);
    func_800AF1B4(menu->unk_04, direction, move_mode);

done:
    return;
}
