/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "engine/menu.h"
#include "slus.h"

typedef struct S_8004FA2C S_8004FA2C;

/* Update menu selection from directional and side-switch input, with key repeat and sound. */
void handle_animated_selection_menu_input(AnimatedSelectionMenuBody *menu) {
    GameWork *input;
    s32 next_index;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 index_delta;

    input = &g_game_work;
    index_delta = 0;
    if ((input->buttons != 0) && (menu->count >= 2)) {
        if (input->buttons & 0xA000) {
            if ((input->pressed_buttons) & 0x2000) {
                index_delta = 1;
                menu->repeat_ticks = 0;
                menu->transition_frames = 4;
            } else if ((input->pressed_buttons) & 0x8000) {
                index_delta = -1;
                menu->repeat_ticks = 0;
                menu->transition_frames = 4;
            } else {
                repeat_ticks = menu->repeat_ticks;
                if (repeat_ticks >= 9) {
                    menu->repeat_ticks = (s32) (repeat_ticks - 2);
                    held_buttons = input->buttons;
                    if (held_buttons & 0x2000) {
                        index_delta = 1;
                        menu->transition_frames = 3;
                    } else if (held_buttons & 0x8000) {
                        index_delta = -1;
                        menu->transition_frames = 3;
                    }
                } else {
                    menu->repeat_ticks = (s32) (repeat_ticks + 1);
                }
            }
        }
        if (index_delta == 0) {
            if ((input->pressed_buttons) & 1) {
                if (primary_actor_record->unk_B0.address != 0) {
                    next_index = find_resolved_selection_menu_index(menu, 1);
                    menu->transition_frames = 4;
                    index_delta = next_index - menu->selected_index;
                }
            } else if ((input->pressed_buttons) & 2) {
                if (primary_actor_record->unk_AC.address != 0) {
                    next_index = find_resolved_selection_menu_index(menu, 0);
                    menu->transition_frames = 4;
                    index_delta = next_index - menu->selected_index;
                }
            }
        }
        if (index_delta != 0) {
            SD_Call(0x504);
            begin_selection_menu_index_change(menu, index_delta);
        }
    }
}
