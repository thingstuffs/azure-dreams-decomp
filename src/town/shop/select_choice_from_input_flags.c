#include "common.h"
#include "shared/game_work.h"

typedef struct TownState {
    u8 pad0[8];
    s32 enabled;
    u8 padC[4];
    s32 flags;
} TownState;

// Selects a choice from enabled town flags, marks its array entry with 4, and returns it.
s32 select_choice_from_input_flags(s32 *choice_values)
{
    s32 choice;
    s32 town_flags;
    s32 selected_value;

    choice = -1;
    if (g_game_work.buttons != 0) {
        town_flags = ((s32)g_game_work.pressed_buttons);
        if (town_flags & 0x40) {
            choice = 2;
        } else if (town_flags & 0x10) {
            choice = 3;
        } else if (town_flags & 0x20) {
            choice = 4;
        }
    }
    selected_value = 4;
    if (choice != -1) {
        choice_values[choice + 3] = selected_value;
    }
    return choice;
}
