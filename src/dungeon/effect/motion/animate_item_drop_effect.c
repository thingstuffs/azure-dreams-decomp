#include "common.h"
#include "dungeon/effect/motion.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/actor/effect.h"

extern s32 item_effect_descriptor;

/* Animate object motion and scale, then signal completion. */
void animate_item_drop_effect(ItemDropEffectBody *object, ObjectPosition *motion, SpriteFrameState *display)
{
    s16 state;
    s32 velocity;
    u16 frames_left;
    u16 scale;

    state = object->state;
    switch (state) {
    case 0:
        if (display->flags & 0x8000) {
            object->state = 2;
            return;
        }
        object->frames_left = 12;
        object->state = (u16)((u16)object->state + 1);
    case 1:
        velocity = motion->velocity_z + 0x30000;
        motion->velocity_z = velocity;
        motion->z.v += velocity;
        scale = display->scale_x;
        if (scale < 0x1000) {
            display->scale_x = scale + 0x50;
            display->scale_y += 0x50;
        }
        frames_left = object->frames_left - 1;
        object->frames_left = frames_left;
        if ((frames_left << 16) != 0) {
            return;
        }
        motion->velocity_z = 0;
        object->state = (u16)((u16)object->state + 1);
        return;
    case 2:
        place_item_at_valid_floor_position(object->grid_x,
                      object->grid_y,
                      (s16)(((u16) motion->z.w.i) - 0x20),
                      &item_effect_descriptor,
                      (u8 *)object + 0x98);
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}
