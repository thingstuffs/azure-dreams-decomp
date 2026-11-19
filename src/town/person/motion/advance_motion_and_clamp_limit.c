#include "common.h"
#include "shared/entity.h"
#include "shared/town_object.h"
#include "town/person/position.h"
#include "town/person/motion.h"
#include "town/person/state.h"
#include "town/player.h"

#include "town/person/object_setup.h"
void func_800CDF94(TownObjectRecord *object, ObjectPosition *unusedArg, SpriteFrameState *initValue);


/* Advance motion, clamp at its limit, and handle the remaining steps. */
void advance_motion_and_clamp_limit(TownObjectRecord *entity, ObjectPosition *motion, SpriteFrameState *context) {
    s16 steps_left;

    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    if (query_lowered_transform_position(motion) < motion->z.w.i) {
        motion->z.w.i = query_lowered_transform_position(motion);
        steps_left = entity->unk_90 - 1;
        entity->unk_90 = steps_left;
        if (steps_left <= 0) {
            motion->velocity_z = 0;
            func_800CDF94(entity, motion, context);
            return;
        }
        if (select_object_setup_path(entity, motion, context) == 0) {
            initialize_actor_reaction_and_fixed_state(entity, motion, context);
            return;
        }
    } else {
        add_vertical_gravity(motion);
    }
}
