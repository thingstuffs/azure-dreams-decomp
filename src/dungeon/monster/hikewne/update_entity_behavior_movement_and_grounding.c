#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry(void *, u8, s8);
extern void select_sprite_entry(void *, u8, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rsin(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern void D_801594D4(void);
extern u8 hikewne_frame_set_8[];
extern u8 hikewne_frame_set_9[];
extern Callback D_8015C168[];


typedef struct S_80158DA8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80158DA8_2;   /* state in update_entity_behavior_movement_and_grounding */

/* Update entity behavior, movement, directional animation, and ground height. */
/* Runs Hikewne state callbacks from D_8015C168, alternates its bobbing idle frames, and resolves ground
 * contact. */
void update_entity_behavior_movement_and_grounding(void *entity, ObjectPosition *motion, SpriteFrameState *sprite)
{
    void *entity_state = entity;
    s16 prev_state;
    s16 direction;
    s16 sprite_direction;
    s32 height;
    s32 bob_phase;
    u32 bob_angle;
    s16 ground_height;
    s16 ground_delta;
    u16 sprite_flags;
    register s32 bob_tick;
    u32 entity_flags;
    s32 prev_bob_offset;
    Callback paused_callback;
    Callback update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        paused_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (paused_callback == (Callback)D_801594D4) {
            paused_callback(entity, motion, sprite, entity);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    prev_state = (s8)(*(u8 *)((u8 *)entity + 0x6D));
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + 0x8C));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_8015C168[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    if ((s16)prev_state != (*(s8 *)((u8 *)entity + 0x6D))) {
        try_move_actor_to_valid_position(entity, motion, sprite, entity);
    }

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;

    if (!((*(u32 *)((u8 *)entity + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->velocity_z += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->velocity_z;
    sprite_flags = sprite->flags;

    if (!(sprite_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80158DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7;
        sprite_direction = direction;
        if ((*(s16 *)((u8 *)entity + 0x94)) != sprite_direction) {
            select_indirect_table_entry(sprite,
                (*(u8 *)((u8 *)(*(u8 **)&sprite->frameTable) + sprite_direction)),
                sprite->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[sprite_direction] != 0) {
                flip_flags = sprite->flags | 1;
            } else {
                flip_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = flip_flags;
        }
        apply_monster_koyaw_data(((S_80158DA8_2 *)entity_state)->unk_1C.s, (u8 *)sprite + 0xC);
        if (!(((S_80158DA8_2 *)entity_state)->unk_1C.u & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            ((S_80158DA8_2 *)entity_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        {
            u32 air_flags;
            air_flags = ((S_80158DA8_2 *)entity_state)->unk_1C.u & 0xF7FFFFFF;
            ((S_80158DA8_2 *)entity_state)->unk_1C.u = air_flags;
            air_flags &= 0x40000;
            if (!air_flags) {
                s32 offset = (*(s32 *)((u8 *)entity + 0xA0));
                (*(u16 *)((u8 *)entity + 0x9E)) = 0;
                (*(s32 *)((u8 *)entity + 0xA0)) = 0;
                (*(s32 *)((u8 *)entity + 0x90)) -= offset;
                if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                    ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                        ((u16) motion->y.w.i),
                        (s16)(((S_80158DA8_2 *)entity_state)->unk_88 - 0x20));
                    ground_delta = ground_height - ((S_80158DA8_2 *)entity_state)->unk_88;
                    if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                        (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                        motion->velocity_z = 0;
                        ((S_80158DA8_2 *)entity_state)->unk_1C.u |= 0x08000000;
                    }
                }
            } else {
                if (!(sprite->flags & 0x40)) {
                    if (*(u8 **)&sprite->frameTable == hikewne_frame_set_8) {
                        if (*(u16 *)&sprite->unk_04 == 0x100) {
                            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
                        }
                        bob_tick = (*(u16 *)((u8 *)entity + 0x9E))++;
                        bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = bob_phase * 0xE3;
                        (*(s32 *)((u8 *)entity + 0xA0)) = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_9;
                            select_sprite_entry(sprite, hikewne_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle
                                + ((S_80158DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_9) {
                        bob_tick = (*(u16 *)((u8 *)entity + 0x9E))++;
                        bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = bob_phase * 0xE3;
                        (*(s32 *)((u8 *)entity + 0xA0)) = rsin(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_frame_set_8;
                            select_sprite_entry(sprite, hikewne_frame_set_8[((g_game_work.view.camera_rotation.parts.viewAngle
                                + ((S_80158DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    }
                }

                if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                    s32 height_adjust = -0x20;
                    height = (*(s16 *)((u8 *)entity + 0x92));
                    entity_flags = (*(u16 *)((u8 *)entity + 0x92));
                    if (height_adjust < height) {
                        height_adjust = entity_flags - 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                    } else {
                        height_adjust = height < -0x28;
                        if (height_adjust) {
                            height_adjust = entity_flags + 8;
                            (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                        }
                    }
                }
            }
        }
    } else {
        sprite->flags = (sprite_flags & 0x800)
            ? (sprite_flags & 0x8FFF)
        : (sprite_flags | 0x7000);
        ((S_80158DA8_2 *)entity_state)->unk_1C.u &= 0xF7FFFFFF;
        if (!(((S_80158DA8_2 *)entity_state)->unk_1C.u & 0x40000)) {
            prev_bob_offset = (*(s32 *)((u8 *)entity + 0xA0));
            (*(u16 *)((u8 *)entity + 0x9E)) = 0;
            (*(s32 *)((u8 *)entity + 0xA0)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= prev_bob_offset;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_height = sample_terrain_surface_height(((u16) motion->x.w.i),
                    ((u16) motion->y.w.i),
                    (s16)(((S_80158DA8_2 *)entity_state)->unk_88 - 0x20));
                ground_delta = ground_height - ((S_80158DA8_2 *)entity_state)->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_delta;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->velocity_z = 0;
                    ((S_80158DA8_2 *)entity_state)->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 **)&sprite->frameTable == hikewne_frame_set_8) {
                    if (*(u16 *)&sprite->unk_04 == 0x100) {
                        (*(u16 *)((u8 *)entity + 0x9E)) = 0;
                    }
                    bob_tick = (*(u16 *)((u8 *)entity + 0x9E))++;
                    bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = bob_phase * 0xE3;
                    (*(s32 *)((u8 *)entity + 0xA0)) = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_9;
                        select_sprite_entry(sprite, hikewne_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle
                            + ((S_80158DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                } else if (*(u8 **)&sprite->frameTable == hikewne_frame_set_9) {
                    bob_tick = (*(u16 *)((u8 *)entity + 0x9E))++;
                    bob_phase = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = bob_phase * 0xE3;
                    (*(s32 *)((u8 *)entity + 0xA0)) = rsin(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_frame_set_8;
                        select_sprite_entry(sprite, hikewne_frame_set_8[((g_game_work.view.camera_rotation.parts.viewAngle
                            + ((S_80158DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                }
            }

            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                s32 height_adjust = -0x20;
                height = (*(s16 *)((u8 *)entity + 0x92));
                entity_flags = (*(u16 *)((u8 *)entity + 0x92));
                if (height_adjust < height) {
                    height_adjust = entity_flags - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                } else {
                    height_adjust = height < -0x28;
                    if (height_adjust) {
                        height_adjust = entity_flags + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_adjust;
                    }
                }
            }
        }
    }

    entity_flags = ((S_80158DA8_2 *)entity_state)->unk_1C.u;
    if (entity_flags & 0x40000000) {
        ((S_80158DA8_2 *)entity_state)->unk_1C.u = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (sprite->unk_24 << 6) | 0x20,
            (sprite->unk_25 << 6) | 0x20,
            (s16)(((S_80158DA8_2 *)entity_state)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (((S_80158DA8_2 *)entity_state)->unk_88 - ground_height) +
                (*(u16 *)((u8 *)entity + 0x92));
            ((S_80158DA8_2 *)entity_state)->unk_88 = ground_height;
        }
    }

    motion->z.w.i = ((S_80158DA8_2 *)entity_state)->unk_88 +
        (*(u16 *)((u8 *)entity + 0x92)) - (*(u16 *)((u8 *)entity + 0xA2));
    sprite->flags |= 0x40;
}
