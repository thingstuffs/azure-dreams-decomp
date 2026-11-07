
struct ObjectPosition;
#include "common.h"
#include "slus/imports.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "dungeon/effect.h"
#include "sdk/libgte.h"
#include "shared/object_node.h"
#include "dungeon/monster/cyclone/bobbing_motion.h"
#include "dungeon/monster/cyclone.h"

extern void select_sprite_entry(void *, s32, s32);

/* Advances motion and output animation, then signals completion after a short delay. */
void advance_motion_output_animation(CycloneBobbingMotionBody *motion, ObjectPosition *position, SpriteFrameState *output) {
    u16 frame_count;
    ObjectNodeHeader *object;

    frame_count = motion->count + 1;
    motion->count = frame_count;
    switch (motion->state) {
    case 0:
        output->scale_y = output->scale_y + 0x40;
        output->scale_x = output->scale_y;
        motion->path.x.v = motion->path.x.v + motion->path.velocity_x;
        position->x.v = motion->path.x.v;
        motion->path.y.v = motion->path.y.v + motion->path.velocity_y;
        position->y.v = motion->path.y.v;
        motion->path.z.v = motion->path.z.v + motion->path.velocity_z;
        position->z.v = motion->path.z.v - ((rsin((s16)motion->count << 6) >> 4) * 0xC000);
        if ((s16)motion->count >= 0x20) {
            motion->count = 0;
            motion->state = motion->state + 1;
        }
        break;
    case 1:
        if ((s16)frame_count < 4) {
            break;
        }
        NODE_HEADER(motion)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    object = NODE_HEADER(motion);
    select_nearby_target_and_initialize_slot(object, position, 8, 0x300);
    advance_sprite_animation_and_textures(output);
    if (output->flags & 0x6000) {
        select_sprite_entry(output, 0x47, 0);
    }

    return;
}
