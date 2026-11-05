/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "shared/runtime_dispatch.h"
#include "town.h"
#include "town/player.h"




/*
 * Selects the linked handler table, clears the indexed object slot, and installs D_80099AC4 with
 * count 0x20.
 */
void init_player_countdown_action(TownObjectRecord *object, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry(object->handler_entries[7], object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = tick_player_countdown;
    object->unk_0A.as_s16 = 0x20;
}
