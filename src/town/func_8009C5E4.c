/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/data.h"

typedef struct S_80099CE0_2 {
    u8 pad_00[0xC];
    s32 unk_08;
} S_80099CE0_2;   

/*
 * Selects the table from the linked record, clears the indexed object slot, and installs
 * record_action_update_address with count 0x15.
 */
void init_twenty_one_tick_record_action_c(TownObjectRecord *object, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) ((S_80099CE0_2 *)(object->unk_44))->unk_08, object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &record_action_update_address;
    object->unk_0A.as_s16 = 0x15;
}
