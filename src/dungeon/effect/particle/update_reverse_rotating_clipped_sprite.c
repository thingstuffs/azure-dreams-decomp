#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "dungeon/effect/particle.h"

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} __attribute__((packed)) Rect;

typedef struct {
    s16 x;
    s16 y;
} Point;

extern Rect D_80164824;
extern void draw_transformed_sprite_with_clip_rect(void *, Rect *, Point *, s32, s32);

/* Updates effect rotation and rectangle, then flags timer expiration. */
void update_reverse_rotating_clipped_sprite(RotatingClippedSpriteBody *effect, ObjectPosition *unused, SpriteFrameState *rotation)
{
    Rect rect;
    Point center;
    u16 ticks_left;
    u16 angle;
    u16 next_angle;
    s32 angle_sign;

    rect = D_80164824;
    center.x = rect.x + ((s16)rect.w >> 1);
    center.y = rect.y + ((s16)rect.h >> 1);

    angle = rotation->angle_z;
    next_angle = angle - 0x28;
    angle_sign = next_angle << 16;
    angle = next_angle;
    if (angle_sign <= 0) {
        angle += 0x1000;
    }
    rotation->angle_z = angle;

    draw_transformed_sprite_with_clip_rect(effect, &rect, &center, 1, 1);

    ticks_left = effect->ticks_remaining - 1;
    effect->ticks_remaining = ticks_left;
    if ((s16)ticks_left <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
