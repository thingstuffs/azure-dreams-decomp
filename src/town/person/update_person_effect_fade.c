#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "town/person/offset_effect_body.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "slus.h"
#include "town/person.h"


/* Update effect motion, fade its brightness, and mark it expired when its timer ends. */
void update_person_effect_fade(void *effect_record, ObjectPosition *motion, SpriteFrameState *primitive) {
    PersonOffsetEffectBody *body = effect_record;
    u16 ticks_left;
    u8 brightness;

    motion->velocity_z = (s32) (motion->velocity_z + (body->vertical_acceleration << 0xB));
    body->vertical_acceleration = (s16) ((u16) body->vertical_acceleration + 1);
    motion->x.v = (s32) (motion->x.v + motion->velocity_x);
    motion->y.v = (s32) (motion->y.v + motion->velocity_y);
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    advance_sprite_animation_and_textures(primitive);
    brightness = primitive->color.c.r;
    if (brightness != 0) {
        brightness = brightness - 0x10;
        primitive->color.c.r = brightness;
        primitive->color.c.b = brightness;
        primitive->color.c.g = brightness;
    }
    ticks_left = body->ticks_left - 1;
    body->ticks_left = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(body)->flags = (u16) (NODE_HEADER(body)->flags | 0x8000);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
