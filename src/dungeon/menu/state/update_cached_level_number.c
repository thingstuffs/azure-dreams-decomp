#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "dungeon/menu.h"
#include "dungeon/menu/state.h"



typedef struct S_800DC5B4_1 {
    u8 pad_00[0x30];
    s32 unk_30;
} S_800DC5B4_1;   /* arg0 in update_cached_level_number */

/* Processes a change in the global state value and updates the cached value. */
void update_cached_level_number(S_800DC5B4_1 *cachedState) {
    u8 currentValue;
    ActorRecord **globalStateSlot;

    globalStateSlot = &primary_actor_record;
    currentValue = (*globalStateSlot)->level;
    if (currentValue != cachedState->unk_30) {
        draw_hud_number_tall(currentValue, cachedState->unk_30, 2, 0x18A, 0x190, 0);
        cachedState->unk_30 = (*globalStateSlot)->level;
    }
}
