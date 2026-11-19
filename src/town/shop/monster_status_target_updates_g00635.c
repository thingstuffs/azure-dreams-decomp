/* Release handled entries and change the monster status target. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B93B0, CL:town/func_800B97F4. */
#include "town/shop/monster_status_target_updates_g00635.h"
#include "records/Rec_func_800B683C_arg0.h"
#include "shared/object_flags.h"
#include "town/shop.h"
#include "town/shop/state.h"

/* Processes 24 entries by type and clears the handle and type of handled entries. */
void release_monster_status_entries(ItemMenuPart **entries) {
    s32 entry_index;
    u8 entry_type;
    ItemMenuPart *entry;
    ItemMenuPartPosition *position;

    for (entry_index = 0; entry_index < 0x18; entry_index++) {
        entry = entries[entry_index];
        position = entry->position;
        entry_type = position->type;
        if (entry_type == 2) {
            flag_optional_object_for_removal(entry->handler);
            entries[entry_index]->handler = 0;
            position = entries[entry_index]->position;
            position->type = 0;
        } else if (entry_type == 1) {
            flag_object_for_removal(entry->handler);
            entries[entry_index]->handler = 0;
            position = entries[entry_index]->position;
            position->type = 0;
        }
    }

}

/* Process an object's pointer array and embedded state, then set its and the global 0x8000 flags. */
void destroy_monster_status_object(ObjectNodeHeader *object)
{
    ShopFirstCallbackObject *objectState;

    if (object != 0) {
        objectState = NODE_BODY(object);
        release_null_terminated_entries(objectState->allocations);
        release_monster_status_entries(objectState->parts);
        release_monster_status_request_handles(objectState);
        object->flags |= 0x8000;
        D_800814A0 |= OBJECT_REMOVE_PENDING;
    }
}

/* Updates the embedded object state and runs its associated helpers. */
void change_monster_status_display_target(s32 objectAddress, struct ActorRecord *actor, s16 field08Value) {
    ShopFirstCallbackObject *objectState;

    if (objectAddress != 0) {
        objectState = NODE_BODY((unsigned long)(u32)objectAddress);
        release_monster_status_entries(objectState->parts);
        objectState->slot_index = field08Value;
        objectState->actor = actor;
        build_monster_status_display(objectState);
        queue_monster_status_reload(objectState);
    }
}
