#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "town/player/state.h"

typedef struct TownCallbacks {
    u8 pad0[0x54];
    s32 (*select)(u32);
} TownCallbacks;

typedef struct TownRoot {
    u8 pad0[0x20];
    TownCallbacks *callbacks;
} TownRoot;

/* Selects an available option and triggers its associated action, or returns -1. */
s32 select_available_option_triggers_associated(void)
{
    s32 available[4];
    s32 choice;

    choice = 0;
    available[0] = 0;
    available[1] = 0;
    available[2] = 0;
    available[3] = 0;

    if (get_script_flag_mask(Ft_selfy_love) != 0) {
        choice = 1;
        available[0] = 1;
    }
    if (get_script_flag_mask(Ft_far_love) != 0) {
        choice += 1;
        available[1] = 1;
    }
    if (get_script_flag_mask(Ft_mia_love) != 0) {
        choice += 1;
        available[2] = 1;
    }
    if (get_script_flag_mask(Ft_niko_love) != 0) {
        choice += 1;
        available[3] = 1;
    }

    if (choice != 0) {
        u32 root_page = 0x80010000;

        {
            s32 *available_flags = available;

            do {
                choice = (*(TownRoot **)(root_page + 0x6000))->callbacks->select(4);
            } while (available_flags[choice] == 0);
        }
        set_script_flag_bit(choice + 0x9B7);
    } else {
        choice = -1;
    }

    return choice;
}
