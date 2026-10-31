#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/level.h"

typedef void (*Func4)(void *, void *, void *, void *);
extern Func4 actor_brightness_callbacks[];
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);

typedef struct S_800D4158_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D4158_1;   /* arg1 in update_actor_motion_and_brightness */

/* Updates entity callbacks, motion, ground contact, and sprite brightness. */
void update_actor_motion_and_brightness(ActorRecord *body, S_800D4158_1 *motion, SpriteFrameState *sprite) {
    void *entity_ref = body;
    u16 motion_flags;
    u32 entity_flags;
    s16 ground_height;
    s32 ground_height_raw;
    s16 pulse_phase;
    s32 brightness;

    if (g_dungeon_status.flags & 0x2000) {
        (*((u8 *)entity_ref + 0x71)) = (*((u8 *)entity_ref + 0x71)) & 0x7f;
        return;
    }
    if ((*(Func4 *)((u8 *)entity_ref + 0x8c)) != NULL) {
        ((Func4)(*(Func4 *)((u8 *)entity_ref + 0x8c)))(entity_ref, motion, sprite, entity_ref);
    }
    actor_brightness_callbacks[(*((u8 *)entity_ref + 0x9a))](entity_ref, motion, sprite, entity_ref);
    if (!(sprite->flags & 0x8000)) {
        if (!(sprite->flags & 0x40)) {
            advance_sprite_animation_and_textures(sprite);
        }
    }
    motion->unk_00.at00.v += motion->unk_0C;
    motion->unk_04.at00.v += motion->unk_10;
    motion_flags = body->action_state_flags;
    if (motion_flags & 8) {
        body->unk_9D.u = 0;
    } else {
        motion->unk_14 += body->unk_9D.s * 0x14000;
        body->unk_9D.s = body->unk_9D.u + 1;
    }
    body->unk_90.value += motion->unk_14;
    if (!(body->action_state_flags & 4) &&
        (ground_height = (s16)(ground_height_raw = sample_terrain_surface_height(motion->unk_00.at02.v, motion->unk_04.at02.v,
                        (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20)))) < 0x200) {
        if (body->unk_90.parts.high.s + (*(s16 *)((u8 *)entity_ref + 0x88)) < ground_height) {
            body->action_state_flags &= 0xF7FFFFFF;
        } else {
            if (ground_height >= (*(s16 *)((u8 *)entity_ref + 0x88))) {
                body->unk_90.value = 0;
            } else {
                body->unk_90.parts.high.s = ground_height_raw - (*(u16 *)((u8 *)entity_ref + 0x88));
            }
            motion->unk_14 = 0;
            (*(s32 *)((u8 *)entity_ref + 0x1c)) |= 0x08000000;
            body->unk_9D.s = 0;
        }
        entity_flags = (*(u32 *)((u8 *)entity_ref + 0x1c));
        if (entity_flags & 0x40000000) {
            (*(u32 *)((u8 *)entity_ref + 0x1c)) = entity_flags & 0xbfffffff;
            ground_height_raw = sample_terrain_surface_height(
                (sprite->tile_x << 6) | 0x20,
                (sprite->tile_y << 6) | 0x20,
                (s16)((*(u16 *)((u8 *)entity_ref + 0x88)) - 0x20));
            body->unk_90.parts.high.s += (*(u16 *)((u8 *)entity_ref + 0x88)) - ground_height_raw;
            (*(s16 *)((u8 *)entity_ref + 0x88)) = ground_height_raw;
        }
    } else {
        (*(u32 *)((u8 *)entity_ref + 0x1c)) &= 0xf7ffffff;
    }
    motion->unk_0A = (*(u16 *)((u8 *)entity_ref + 0x88)) +
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
