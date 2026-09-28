/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_8004FAA4_1 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
} S_8004FAA4_1;   /* arg0 in func_8004FAA4 */


M2C_UNK func_8004FA2C();
s32 func_8004FD78();
M2C_UNK SD_Call();

/* Update menu selection from directional and side-switch input, with key repeat and sound. */
void func_8004FAA4(S_8004FAA4_1 *menu) {
    M2C_UNK target_side;
    GameWork *input;
    void *target_menu;
    s32 next_index;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 index_delta;

    input = &gameWork;
    index_delta = 0;
    if ((input->buttons != 0) && (menu->unk_24 >= 2)) {
        if (input->buttons & 0xA000) {
            if (((s32)input->unk_010) & 0x2000) {
                index_delta = 1;
                goto start_repeat;
            }
            if (((s32)input->unk_010) & 0x8000) {
                index_delta = -1;
start_repeat:
                menu->unk_38 = 0;
                menu->unk_28 = 4;
            } else {
                repeat_ticks = menu->unk_38;
                if (repeat_ticks >= 9) {
                    menu->unk_38 = (s32) (repeat_ticks - 2);
                    held_buttons = input->buttons;
                    if (held_buttons & 0x2000) {
                        index_delta = 1;
                        goto repeat_move;
                    }
                    if (held_buttons & 0x8000) {
                        index_delta = -1;
repeat_move:
                        menu->unk_28 = 3;
                    }
                } else {
                    menu->unk_38 = (s32) (repeat_ticks + 1);
                }
            }
        }
        if (index_delta == 0) {
            if (((s32)input->unk_010) & 1) {
                if (((s32)D_800814A8->unk_B0) != 0) {
                    target_menu = menu;
                    target_side = 1;
                    goto select_target;
                }
            } else if (((s32)input->unk_010) & 2) {
                if (((s32)D_800814A8->unk_AC) != 0) {
                    target_menu = menu;
                    target_side = 0;
select_target:
                    next_index = func_8004FD78(target_menu, target_side);
                    menu->unk_28 = 4;
                    index_delta = next_index - menu->unk_30;
                }
            }
            if (index_delta != 0) {
                goto apply_move;
            }
        } else {
apply_move:
            SD_Call(0x504);
            func_8004FA2C(menu, index_delta);
        }
    }
}
