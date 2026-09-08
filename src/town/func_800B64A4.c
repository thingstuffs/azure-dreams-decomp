#include "common.h"

typedef struct TownState {
    u8 pad0[8];
    s32 enabled;
    u8 padC[4];
    s32 flags;
} TownState;

extern TownState D_80083160;

// Selects a choice from enabled town flags, marks its array entry with 4, and returns it.
s32 func_800B3C04(s32 *choice_values)
{
    s32 choice;
    s32 town_flags;
    s32 selected_value;
    TownState *town_state;

    town_state = &D_80083160;
    choice = -1;
    if (town_state->enabled != 0) {
        town_flags = town_state->flags;
        if (town_flags & 0x40) {
            choice = 2;
            goto selected;
        }
        if (town_flags & 0x10) {
            choice = 3;
            goto selected;
        }
        if (town_flags & 0x20) {
            choice = 4;
        }
    }
selected:
    selected_value = 4;
    if (choice != -1) {
        choice_values[choice + 3] = selected_value;
    }
    return choice;
}
