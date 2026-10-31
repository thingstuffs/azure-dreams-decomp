#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"
#include "dungeon/item.h"
#include "engine/texture.h"

typedef ActorActionHandler Callback;

extern void select_sprite_entry(void *, u8, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);

extern void D_8016B4D4(void);
extern u8 hikewne_frame_set_14[];
extern u8 hikewne_frame_set_15[];
extern Callback D_8016E168[];


typedef struct S_8016ADA8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8016ADA8_2;   /* state in update_entity_behavior_movement_and_height */

/* Updates entity behavior, movement, directional animation, and ground-relative height. */
/* Runs Hikewne state callbacks from D_8016E168, alternates its bobbing idle frames, and resolves ground
 * contact. */
void update_entity_behavior_movement_and_height(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_8016ADA8_2 *entity_state = (S_8016ADA8_2 *)body;
    s16 old_state_id;
    s16 direction;
    s16 sprite_direction;
    s32 height_offset;
    s32 bob_phase;
    u32 bob_angle;
    s16 ground_height;
    s16 ground_delta;
    u16 sprite_flags;
    register s32 bob_tick;
    u32 entity_flags;
    s32 bob_offset;
    Callback paused_callback;
    Callback update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = body->unk_8C.handler;
        if (paused_callback == (Callback)D_8016B4D4) {
            paused_callback(body, motion, sprite, body);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }

    old_state_id = (s8)(*((u8 *)body + 0x6D));
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    update_callback = body->unk_8C.handler;
    if (update_callback != 0) {
        update_callback(body, motion, sprite, body);
    }
    D_8016E168[body->action_id.u](body, motion, sprite, body);
    if ((s16)old_state_id != body->pending_turn_updates) {
        try_move_actor_to_valid_position(body, motion, sprite, body);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (!((*(u32 *)((u8 *)body + 0x1C)) & 0x40000) &&
        !(body->action_state_flags & 8)) {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    } else {
        body->unk_9D.u = 0;
    }
    body->unk_90.value += motion->velocity_z;
    sprite_flags = sprite->flags;

    if (!(sprite_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_state->unk_2A + 0x100) >> 9) & 7;
        sprite_direction = direction;
        if (body->unk_94 != sprite_direction) {
            select_indirect_table_entry(sprite,
                (*((u8 *)(*(u8 **)&sprite->frameTable) + sprite_direction)),
                sprite->unk_04);
            body->unk_94 = direction;
        }
        {
            u32 facing_flags;
            if (dir_sprite_flag[sprite_direction] != 0) {
                facing_flags = sprite->flags | 1;
            } else {
                facing_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = facing_flags;
        }
        apply_monster_koyaw_data(entity_state->unk_1C.s, (u8 *)sprite + 0xC);
        if (!(entity_state->unk_1C.u & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            entity_state->unk_1C.u &= 0xFFFBFFFF;
        }

        {
            u32 masked_flags;
            masked_flags = entity_state->unk_1C.u & 0xF7FFFFFF;
            entity_state->unk_1C.u = masked_flags;
            masked_flags &= 0x40000;
            if (!masked_flags) {
                s32 offset = body->unk_A0.value;
                body->unk_9E.u = 0;
                body->unk_A0.value = 0;
                body->unk_90.value -= offset;
                if (!(body->action_state_flags & 8)) {
                    ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                        ((u16) motion->y.w.i),
                        (s16)(entity_state->unk_88 - 0x20));
                    ground_delta = ground_height - entity_state->unk_88;
                    if (ground_delta < body->unk_90.parts.high.s) {
                        body->unk_90.parts.high.s = ground_delta;
                        body->unk_9D.u = 0;
                        motion->velocity_z = 0;
                        entity_state->unk_1C.u |= 0x08000000;
                    }
                }
            } else {
                if (!(sprite->flags & 0x40)) {
                    if (*(u8 **)&sprite->frameTable == hikewne_frame_set_14) {
                        if (*(u16 *)&sprite->unk_04 == 0x100) {
                            body->unk_9E.u = 0;
                        }
                        bob_tick = body->unk_9E.u++;
                        bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = bob_phase * 0xE3;
                        body->unk_A0.value = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_15;
                            select_sprite_entry(sprite, hikewne_frame_set_15[((g_game_work.view.camera_rotation.parts.viewAngle
                                + entity_state->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_15) {
                        bob_tick = body->unk_9E.u++;
                        bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = bob_phase * 0xE3;
                        body->unk_A0.value = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_14;
                            select_sprite_entry(sprite, hikewne_frame_set_14[((g_game_work.view.camera_rotation.parts.viewAngle
                                + entity_state->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    }
                }

                if (!(body->action_state_flags & 8)) {
                    s32 height_work = -0x20;
                    height_offset = body->unk_90.parts.high.s;
                    entity_flags = body->unk_90.parts.high.u;
                    if (height_work < height_offset) {
                        height_work = entity_flags - 8;
                        body->unk_90.parts.high.s = height_work;
                    } else {
                        height_work = height_offset < -0x28;
                        if (height_work) {
                            height_work = entity_flags + 8;
                            body->unk_90.parts.high.s = height_work;
                        }
                    }
                }
            }
        }
    } else {
        sprite->flags = (sprite_flags & 0x800)
            ? (sprite_flags & 0x8FFF)
        : (sprite_flags | 0x7000);
        entity_state->unk_1C.u &= 0xF7FFFFFF;
        if (!(entity_state->unk_1C.u & 0x40000)) {
            bob_offset = body->unk_A0.value;
            body->unk_9E.u = 0;
            body->unk_A0.value = 0;
            body->unk_90.value -= bob_offset;
            if (!(body->action_state_flags & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                    ((u16) motion->y.w.i),
                    (s16)(entity_state->unk_88 - 0x20));
                ground_delta = ground_height - entity_state->unk_88;
                if (ground_delta < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = ground_delta;
                    body->unk_9D.u = 0;
                    motion->velocity_z = 0;
                    entity_state->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 **)&sprite->frameTable == hikewne_frame_set_14) {
                    if (*(u16 *)&sprite->unk_04 == 0x100) {
                        body->unk_9E.u = 0;
                    }
                    bob_tick = body->unk_9E.u++;
                    bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = bob_phase * 0xE3;
                    body->unk_A0.value = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_15;
                        select_sprite_entry(sprite, hikewne_frame_set_15[((g_game_work.view.camera_rotation.parts.viewAngle
                            + entity_state->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_15) {
                    bob_tick = body->unk_9E.u++;
                    bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = bob_phase * 0xE3;
                    body->unk_A0.value = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_14;
                        select_sprite_entry(sprite, hikewne_frame_set_14[((g_game_work.view.camera_rotation.parts.viewAngle
                            + entity_state->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                }
            }

            if (!(body->action_state_flags & 8)) {
                s32 height_work = -0x20;
                height_offset = body->unk_90.parts.high.s;
                entity_flags = body->unk_90.parts.high.u;
                if (height_work < height_offset) {
                    height_work = entity_flags - 8;
                    body->unk_90.parts.high.s = height_work;
                } else {
                    height_work = height_offset < -0x28;
                    if (height_work) {
                        height_work = entity_flags + 8;
                        body->unk_90.parts.high.s = height_work;
                    }
                }
            }
        }
    }
    entity_flags = entity_state->unk_1C.u;
    if (entity_flags & 0x40000000) {
        entity_state->unk_1C.u = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (sprite->tile_x << 6) | 0x20,
            (sprite->tile_y << 6) | 0x20,
            (s16)(entity_state->unk_88 - 0x20));
        if (ground_height < 0x200) {
            body->unk_90.parts.high.s =
                (entity_state->unk_88 - ground_height) +
                body->unk_90.parts.high.u;
            entity_state->unk_88 = ground_height;
        }
    }

    motion->z.w.i = entity_state->unk_88 +
        body->unk_90.parts.high.u - body->unk_A0.parts.high;
    sprite->flags |= 0x40;
}
