#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/person/state.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern void D_800C5ADC();
extern s32 D_800D54BC[];


/* Initialize the actor, clear its table flag, and install its handler. */
void initialize_actor_clear_table_flag(TownObjectRecord *actor, s32 unused, void *init_param) {
    initialize_object_entries((actor), init_param, D_800D54BC);
    object_index_slots[actor->slot].unk_00 = 0;
    actor->handler = &D_800C5ADC;
}
