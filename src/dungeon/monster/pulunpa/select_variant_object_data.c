#include "common.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/pulunpa.h"
#include "dungeon/actor.h"


extern u8 pulunpa_action_resume_address;
extern u8 pulunpa_variant_action_address;

/* Selects object data from its variant flag when the condition is met. */
void select_variant_object_data(void *object, void *motion, void *params, void *extra)
{
    u8 *selected_data;

    if (update_actor_hop_and_grow(object, motion, params, extra) != 0) {
        if (*(u8 *)((u8 *)object + 0xA7) != 0) {
            selected_data = &pulunpa_variant_action_address;
        } else {
            selected_data = &pulunpa_action_resume_address;
        }
        *(u8 **)((u8 *)object + 0x8C) = selected_data;
    }
}
