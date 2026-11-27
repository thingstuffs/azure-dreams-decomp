/* Recovered retail twin. */
#include "common.h"
#include "town/player/object_initialization_g00546.h"
#include "town/player/scene_action_setup.h"
#include "shared/object_index_slots.h"
#include "shared/town_handler.h"
#include "town/player/object.h"
#include "town.h"
#include "town/player/state.h"

typedef struct SceneActionReset {
     s8 unk0[4];
     void *action_callback;
     s8 unk8[2];
     s16 action_countdown;
} SceneActionReset;

extern u8 D_800D01D8[];


/*
 * Selects D_800D01D8, clears both bytes of object slot one and the entity motion fields, and
 * installs target_action_update_address with count 0x15.
 */
void init_stopped_target_action(SceneActionReset *object, void *position, void *handler_context) {
    dispatch_selected_entry_if_nonzero((s32 *) D_800D01D8, (TownObjectRecord *) object, handler_context);
    object_index_slots[1].motion_id = 0;
    object_index_slots[1].active = 0;
    object->action_callback = target_action_update_address;
    object->action_countdown = 0x15;
    clear_object_velocity(position);
}
