#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "dungeon/monster/cyclone.h"
#include "sdk/libgte.h"
#include "slus.h"

/* Updates radial position or sets completion flags based on the object state. */
void update_radial_motion_or_complete(RandomizedMotionObjectBody *motion, s32 *position, SpriteFrameState *object)
{
    s32 y_offset;
    union {
        RandomizedMotionObjectBody *body;
        u16 *words;
    } body_view;

    body_view.body = motion;
    motion->update_count++;
    advance_sprite_animation_and_textures(object);
    if (object->flags & 0x6000) {
        body_view.words[-1] |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    motion->radius += motion->radius_growth;
    position[0] = position[3] + (((rcos(motion->phase) >> 4) *
                           (s16)motion->radius) << 8);
    y_offset = (rsin(motion->phase) >> 4) * (s16)motion->radius;
    *(u16 *)((u8 *)position + 0xA) -= 2;
    position[1] = position[4] + (y_offset << 8);
}
