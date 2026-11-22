#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"


/* The +8 position link of the scene-list anchor. */
extern ObjectPosition *D_800834A0;

#include "town/person/object_setup.h"
#include "town/person/motion.h"
#include "town/person/object.h"



/* Move the output toward the target position until the object countdown expires. */
void move_mother_event_output_to_target(TownObjectRecord *object, ObjectPosition *out, struct SpriteFrameState *sprite) {
    s16 signed_frames;
    u16 target_x;
    u16 target_y;
    u16 frames;

    target_x = D_800834A0->x.w.i;
    target_y = D_800834A0->y.w.i - 0x42;
    frames = object->timer - 1;
    object->timer = frames;
    signed_frames = (s32)((u32)frames << 16) >> 16;

    if (signed_frames <= 0) {
        apply_object_setup_and_update(object, out, sprite);
        out->x.unsigned_parts.integer = target_x;
        out->y.w.i = target_y;
        return;
    }

    out->x.unsigned_parts.integer =
        (u16)(out->x.unsigned_parts.integer +
              ((s16)target_x - (s16)out->x.unsigned_parts.integer) /
              signed_frames);
    out->y.w.i =
        (s16)((u16)out->y.w.i +
              ((s16)target_y - out->y.w.i) /
              (s16)object->timer);
}
