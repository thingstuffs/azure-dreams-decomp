#include "common.h"
#include "shared/object_index_slots.h"

#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/state.h"
#include "town/person/object.h"

extern s32 D_800D68D4[];

/* Initializes an entity, sets its state to 6, and copies its table entry's byte. */
void initialize_entity_action_state(TownObjectRecord *entity, s32 unused, void *init_value) {
    initialize_object_entries(entity, init_value, D_800D68D4);
    (*(u8 *)&object_index_slots[entity->slot].unk_00) = 0;
    entity->handler = update_entity_countdown_completion;
    entity->timer.as_s16 = 6;
    entity->variant.as_u8 = object_index_slots[entity->slot].unk_02;
}
