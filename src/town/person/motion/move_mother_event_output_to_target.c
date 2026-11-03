#include "common.h"
#include "shared/town_object.h"
#include "shared/dungeon_moving_views.h"


extern void *D_800834A0;

#include "town/person/object_setup.h"
#include "town/person/motion.h"
#include "town/person/object.h"



/* Move the output toward the target position until the object countdown expires. */
void move_mother_event_output_to_target(void *object_arg, void *out_arg, void *setup_context) {
    ObjectPosition *out = out_arg;
    TownObjectRecord *object = object_arg;
    s16 signed_frames;
    u16 target_x;
    u16 target_y;
    u16 frames;

    target_x = ((MovingPosition *)D_800834A0)->x;
    target_y = ((MovingPosition *)D_800834A0)->y - 0x42;
    frames = object->timer.as_u16 - 1;
    object->timer.as_u16 = frames;
    signed_frames = (s32)((u32)frames << 16) >> 16;

    if (signed_frames <= 0) {
        apply_object_setup_and_update(object, out, setup_context);
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
              (s16)object->timer.as_u16);
}
