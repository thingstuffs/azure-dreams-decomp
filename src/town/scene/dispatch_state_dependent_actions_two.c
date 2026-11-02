#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"
#include "town/player/state.h"

typedef struct TownCallback {
    u8 pad_00[0x218];
    void (*callback)(void *);
} TownCallback;

typedef struct TownRoot {
    u8 pad_00[0x20];
    TownCallback *callback;
} TownRoot;

extern s32 D_800190D4;

/* Dispatches state-dependent actions for two IDs, then invokes the town callback. */
void dispatch_state_dependent_actions_two(void)
{
    void *callback_arg;
    TownRoot *town_root;

    if (get_script_flag_mask(F_sbs13_pad08) != 0) {
        clear_script_flag_bit(F_sbs13_pad08);
    } else {
        set_script_flag_bit(F_sbs13_pad08);
    }

    if (get_script_flag_mask(F_player_mizugi) != 0) {
        clear_script_flag_bit(F_player_mizugi);
    } else {
        set_script_flag_bit(F_player_mizugi);
    }

    callback_arg = &D_800190D4;
    town_root = (TownRoot *)town_scene_root;
    town_root->callback->callback(callback_arg);
}
