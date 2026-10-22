#include "common.h"
#include "shared/object_flags.h"

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
void update_reverse_rotating_clipped_sprite(void *effect, s32 unused, void *rotation)
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

    angle = *(u16 *)((u8 *)rotation + 0x1A);
    next_angle = angle - 0x28;
    angle_sign = next_angle << 16;
    angle = next_angle;
    if (angle_sign <= 0) {
        angle += 0x1000;
    }
    *(u16 *)((u8 *)rotation + 0x1A) = angle;

    draw_transformed_sprite_with_clip_rect(effect, &rect, &center, 1, 1);

    ticks_left = *(u16 *)((u8 *)effect + 0x18) - 1;
    *(u16 *)((u8 *)effect + 0x18) = ticks_left;
    if ((s16)ticks_left <= 0) {
        *(u16 *)((u8 *)effect - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
