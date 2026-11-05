#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "town/map/timed_primitive_body.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"
#include "town/map.h"

/* Fades the primitive and sets completion flags when the countdown expires. */
void fade_timed_primitive(void *record_fields, void *unused, SpriteFrameState *primitive) {
    TimedPrimitiveBody *body = record_fields;
    u16 ticks_left;
    u8 brightness;
    u8 unused_byte;

    advance_sprite_animation_and_textures(primitive);
    brightness = primitive->color.c.r;
    if (brightness != 0) {
        primitive->color.c.r = (brightness - 0x10);
        primitive->color.c.b = (brightness - 0x10);
        primitive->color.c.g = (brightness - 0x10);
    }
    ticks_left = body->ticks_left - 1;
    body->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(body)->flags = (u16) (NODE_HEADER(body)->flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
    }
}
