/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "town/player/scene_action_setup.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "town/player/object.h"

typedef struct SceneActionReset {
     s8 unk0[4];
     void *unk4;
     s8 unk8[2];
     s16 unkA;
} SceneActionReset;

extern u8 D_800D01D8[];


/*
 * Selects D_800D01D8, clears both bytes of object slot one and the entity motion fields, and
 * installs target_action_update_address with count 0x15.
 */
void initialize_scene_state_twenty_one(SceneActionReset *object, void *position, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) D_800D01D8, (Rec_func_80094268_arg0 *) object, handler_context);
    object_index_slots[1].unk_00 = 0;
    object_index_slots[1].unk_01 = 0;
    object->unk4 = target_action_update_address;
    object->unkA = 0x15;
    clear_entity_record_fields(position);
}
