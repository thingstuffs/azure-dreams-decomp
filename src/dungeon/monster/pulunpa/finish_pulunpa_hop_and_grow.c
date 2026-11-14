#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"


extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_variant_action_address;

/* Selects object data from its variant flag when the condition is met. */
void finish_pulunpa_hop_and_grow(ActorRecord *object, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *extra)
{
    u8 *selected_data;

    if (update_actor_hop_and_grow(object, motion, sprite, extra) != 0) {
        if (object->unk_A4.bytes[3] != 0) {
            selected_data = &pulunpa_variant_action_address;
        } else {
            selected_data = &pulunpa_action_resume_address;
        }
        object->unk_8C.byte_ptr = selected_data;
    }
}
