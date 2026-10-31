#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "dungeon/actor/state.h"
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"
extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_variant_action_address;

/* Selects object data from its variant flag when the query returns positive. */
void select_variant_object_data_when_positive(ActorRecord *object, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    u8 *selected_data;

    if (resolve_actor_floor_trap_once(object, position, sprite, actor) > 0) {
        if (object->unk_A4.bytes[3] != 0) {
            selected_data = &pulunpa_variant_action_address;
        } else {
            selected_data = &pulunpa_action_resume_address;
        }
        object->unk_8C.byte_ptr = selected_data;
    }
}
