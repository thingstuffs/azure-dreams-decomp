#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "dungeon/actor/state.h"
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"
extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_variant_action_address;

/* Selects object data from its variant flag when the query returns positive. */
void select_variant_object_data_when_positive(void *object, ObjectPosition *unused, SpriteFrameState *source, ActorRecord *target) {
    u8 *selected_data;

    if (resolve_actor_floor_trap_once(object, unused, source, target) > 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &pulunpa_variant_action_address;
        } else {
            selected_data = &pulunpa_action_resume_address;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
