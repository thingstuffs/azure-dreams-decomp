#include "common.h"
#include "town/person/jump_motion.h"

s32 func_800CD158(TownObjectRecord *, s32, struct SpriteFrameState *, s16);

/* Start the registered jump with a vertical velocity of -10. */
void move_flag_object_with_step_minus_10(TownObjectRecord *object, s32 motion, struct SpriteFrameState *sprite) {
    func_800CD158(object, motion, sprite, -10);
}
