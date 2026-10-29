#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"

typedef struct TownCallback {
    u8 pad_00[0x218];
    void (*callback)(void *);
} TownCallback;

typedef struct TownRoot {
    u8 pad_00[0x20];
    TownCallback *callback;
} TownRoot;

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void func_8001886C(s32);
extern s32 D_800190D4;

/* Dispatches state-dependent actions for two IDs, then invokes the town callback. */
void dispatch_state_dependent_actions_two(void)
{
    void *callback_arg;
    TownRoot *town_root;

    if (func_80018964(F_sbs13_pad08) != 0) {
        func_800188E4(F_sbs13_pad08);
    } else {
        func_8001886C(F_sbs13_pad08);
    }

    if (func_80018964(F_player_mizugi) != 0) {
        func_800188E4(F_player_mizugi);
    } else {
        func_8001886C(F_player_mizugi);
    }

    callback_arg = &D_800190D4;
    town_root = *(TownRoot **)((s8 *)(&town_scene_root));
    town_root->callback->callback(callback_arg);
}
