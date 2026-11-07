#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/level.h"
#include "dungeon/actor/motion.h"
#include "sdk/libgte.h"

typedef void (*Func4)(void *, void *, void *, void *);
extern Func4 actor_brightness_callbacks[];
extern void advance_sprite_animation_and_textures(void *);

/* Updates entity callbacks, motion, ground contact, and sprite brightness. */
void update_actor_motion_and_brightness(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite) {
    ActorRecord *entity_ref = body;
    u16 motion_flags;
    u32 entity_flags;
    s16 ground_height;
    s32 ground_height_raw;
    s16 pulse_phase;
    s32 brightness;

    if (g_dungeon_status.flags & 0x2000) {
        entity_ref->movement_queue_state = entity_ref->movement_queue_state & 0x7f;
        return;
    }
    if (entity_ref->unk_8C.run != NULL) {
        entity_ref->unk_8C.run(entity_ref, motion, sprite, entity_ref);
    }
    actor_brightness_callbacks[entity_ref->action_id](entity_ref, motion, sprite, entity_ref);
    if (!(sprite->flags & 0x8000)) {
        if (!(sprite->flags & 0x40)) {
            advance_sprite_animation_and_textures(sprite);
        }
    }
    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion_flags = body->action_state_flags;
    if (motion_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.s = body->unk_9D.u + 1;
    }
    body->unk_90.value += motion->velocity_z;
    if (!(body->action_state_flags & 4) &&
        (ground_height = (s16)(ground_height_raw = sample_terrain_surface_height(motion->x.unsigned_parts.integer, motion->y.unsigned_parts.integer,
                        (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20)))) < 0x200) {
        if (body->unk_90.parts.high.s + entity_ref->ground_height < ground_height) {
            body->action_state_flags &= 0xF7FFFFFF;
        } else {
            if (ground_height >= entity_ref->ground_height) {
                body->unk_90.value = 0;
            } else {
                body->unk_90.parts.high.s = ground_height_raw - (*(u16 *)((u8 *)entity_ref + 0x88));
            }
            motion->velocity_z = 0;
            entity_ref->flags1C |= 0x08000000;
            body->unk_9D.s = 0;
        }
        entity_flags = (*(u32 *)((u8 *)entity_ref + 0x1c));
        if (entity_flags & 0x40000000) {
            entity_ref->flags1C = entity_flags & 0xbfffffff;
            ground_height_raw = sample_terrain_surface_height(
                (sprite->tile_x << 6) | 0x20,
                (sprite->tile_y << 6) | 0x20,
                (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20));
            body->unk_90.parts.high.s += (*(u16 *)((u8 *)entity_ref + 0x88)) - ground_height_raw;
            entity_ref->ground_height = ground_height_raw;
        }
    } else {
        (*(u32 *)((u8 *)entity_ref + 0x1c)) &= 0xf7ffffff;
    }
    motion->z.w.i = (*(u16 *)((u8 *)entity_ref + 0x88)) +
                                   body->unk_90.parts.high.s;
    pulse_phase = body->unk_9E.u;
    pulse_phase++;
    pulse_phase %= 96;
    body->unk_9E.u = pulse_phase;
    if ((s16)pulse_phase < 0x19) {
        brightness = (rsin((s16)pulse_phase * 0x55) >> 4) * 0x60;
        brightness = (brightness >> 8) + 0x80;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
    } else {
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
    }
    sprite->flags |= 0x40;
    (*(u32 *)((u8 *)entity_ref + 0x1c)) |= 0x200;
    return;
}
