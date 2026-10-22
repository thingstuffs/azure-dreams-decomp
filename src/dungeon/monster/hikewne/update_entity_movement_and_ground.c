#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry(void *, u8, s8);
extern void select_sprite_entry(void *, u8, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 func_800644B8(s32);
extern void apply_monster_koyaw_data(s32, void *);
extern s32 refresh_actor_facing_and_lifecycle(void *, void *, void *, void *);
extern void try_move_actor_to_valid_position(void *, void *, void *, void *);
extern s16 sample_terrain_surface_height(u16, u16, s16);

extern void D_801714D4(void);
extern u8 D_801740E0[];
#include "dungeon/monster/hikewne.h"
extern Callback D_80174168[];

typedef struct S_80170DA8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80170DA8_0;   /* arg1 in update_entity_movement_and_ground */

typedef struct S_80170DA8_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80170DA8_2;   /* state in update_entity_movement_and_ground */

/* Update entity behavior, movement, directional animation, and ground height. */
/* Runs Hikewne state callbacks from D_80174168, alternates its bobbing idle frames, and resolves ground
 * contact. */
void update_entity_movement_and_ground(void *entity, void *motion, SpriteFrameState *sprite)
{
    void *entity_state = entity;
    s16 previous_state;
    s16 sprite_direction;
    s16 anim_direction;
    s32 height_offset;
    s32 signed_tick;
    u32 bob_angle;
    s16 ground_height;
    s16 ground_delta;
    u16 sprite_flags;
    register s32 bob_tick;
    u32 entity_flags;
    s32 bob_offset;
    Callback pause_callback;
    Callback update_callback;

    if (g_dungeon_status.flags & 0x2000) {
        pause_callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (pause_callback == (Callback)D_801714D4) {
            pause_callback(entity, motion, sprite, entity);
            return;
        }
        (*(u8 *)((u8 *)entity + (0x71))) &= 0x7F;
        return;
    }

    previous_state = (s8)(*(u8 *)((u8 *)entity + (0x6D)));
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    update_callback = (*(Callback *)((u8 *)entity + (0x8C)));
    if (update_callback != 0) {
        update_callback(entity, motion, sprite, entity);
    }
    D_80174168[(*(u8 *)((u8 *)entity + (0x9A)))](entity, motion, sprite, entity);
    if ((s16)previous_state != (*(s8 *)((u8 *)entity + (0x6D)))) {
        try_move_actor_to_valid_position(entity, motion, sprite, entity);
    }

    ((S_80170DA8_0 *)motion)->unk_00.at00.v += ((S_80170DA8_0 *)motion)->unk_0C;
    ((S_80170DA8_0 *)motion)->unk_04.at00.v += ((S_80170DA8_0 *)motion)->unk_10;

    if (!((*(u32 *)((u8 *)entity + (0x1C))) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
        ((S_80170DA8_0 *)motion)->unk_14 += (*(s8 *)((u8 *)entity + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)entity + (0x9D)))++;
    } else {
        (*(u8 *)((u8 *)entity + (0x9D))) = 0;
    }
    (*(s32 *)((u8 *)entity + (0x90))) += ((S_80170DA8_0 *)motion)->unk_14;
    sprite_flags = sprite->flags;

    if (!(sprite_flags & 0x8000)) {
        sprite_direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7;
        anim_direction = sprite_direction;
        if ((*(s16 *)((u8 *)entity + (0x94))) != anim_direction) {
            select_indirect_table_entry(sprite,
                (*(u8 *)((u8 *)(*(u8 **)&sprite->frameTable) + (anim_direction))),
                sprite->unk_04);
            (*(s16 *)((u8 *)entity + (0x94))) = sprite_direction;
        }
        {
            u32 flip_flags;
            if (dir_sprite_flag[anim_direction] != 0) {
                flip_flags = sprite->flags | 1;
            } else {
                flip_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = flip_flags;
        }
        apply_monster_koyaw_data(((S_80170DA8_2 *)entity_state)->unk_1C.s, (u8 *)sprite + 0xC);
        if (!(((S_80170DA8_2 *)entity_state)->unk_1C.u & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            ((S_80170DA8_2 *)entity_state)->unk_1C.u &= 0xFFFBFFFF;
        }

        {
            u32 airborne_flags;
            airborne_flags = ((S_80170DA8_2 *)entity_state)->unk_1C.u & 0xF7FFFFFF;
            ((S_80170DA8_2 *)entity_state)->unk_1C.u = airborne_flags;
            airborne_flags &= 0x40000;
            if (!airborne_flags) {
                s32 offset = (*(s32 *)((u8 *)entity + (0xA0)));
                (*(u16 *)((u8 *)entity + (0x9E))) = 0;
                (*(s32 *)((u8 *)entity + (0xA0))) = 0;
                (*(s32 *)((u8 *)entity + (0x90))) -= offset;
                if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                    ground_height = sample_terrain_surface_height(((S_80170DA8_0 *)motion)->unk_00.at02.v,
                        ((S_80170DA8_0 *)motion)->unk_04.at02.v,
                        (s16)(((S_80170DA8_2 *)entity_state)->unk_88 - 0x20));
                    ground_delta = ground_height - ((S_80170DA8_2 *)entity_state)->unk_88;
                    if (ground_delta < (*(s16 *)((u8 *)entity + (0x92)))) {
                        (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                        (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                        ((S_80170DA8_0 *)motion)->unk_14 = 0;
                        ((S_80170DA8_2 *)entity_state)->unk_1C.u |= 0x08000000;
                    }
                }
            } else {
                if (!(sprite->flags & 0x40)) {
                    if (*(u8 **)&sprite->frameTable == D_801740E0) {
                        if (*(u16 *)&sprite->unk_04 == 0x100) {
                            (*(u16 *)((u8 *)entity + (0x9E))) = 0;
                        }
                        bob_tick = (*(u16 *)((u8 *)entity + (0x9E)))++;
                        signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = signed_tick * 0xE3;
                        (*(s32 *)((u8 *)entity + (0xA0))) = func_800644B8(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = hikewne_alt_direction_frames;
                            select_sprite_entry(sprite, hikewne_alt_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle
                                + ((S_80170DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    } else if (*(u8 **)&sprite->frameTable == hikewne_alt_direction_frames) {
                        bob_tick = (*(u16 *)((u8 *)entity + (0x9E)))++;
                        signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                        bob_angle = signed_tick * 0xE3;
                        (*(s32 *)((u8 *)entity + (0xA0))) = func_800644B8(bob_angle) << 7;
                        if (*(u16 *)&sprite->unk_04 == 0x103) {
                            (sprite->frameTable) = D_801740E0;
                            select_sprite_entry(sprite, D_801740E0[((g_game_work.view.camera_rotation.parts.viewAngle
                                + ((S_80170DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                        }
                    }
                }

                if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                    s32 height_adjust = -0x20;
                    height_offset = (*(s16 *)((u8 *)entity + (0x92)));
                    entity_flags = (*(u16 *)((u8 *)entity + (0x92)));
                    if (height_adjust < height_offset) {
                        height_adjust = entity_flags - 8;
                        (*(s16 *)((u8 *)entity + (0x92))) = height_adjust;
                    } else {
                        height_adjust = height_offset < -0x28;
                        if (height_adjust) {
                            height_adjust = entity_flags + 8;
                            (*(s16 *)((u8 *)entity + (0x92))) = height_adjust;
                        }
                    }
                }
            }
        }
    } else {
        sprite->flags = (sprite_flags & 0x800)
            ? (sprite_flags & 0x8FFF)
        : (sprite_flags | 0x7000);
        ((S_80170DA8_2 *)entity_state)->unk_1C.u &= 0xF7FFFFFF;
        if (!(((S_80170DA8_2 *)entity_state)->unk_1C.u & 0x40000)) {
            bob_offset = (*(s32 *)((u8 *)entity + (0xA0)));
            (*(u16 *)((u8 *)entity + (0x9E))) = 0;
            (*(s32 *)((u8 *)entity + (0xA0))) = 0;
            (*(s32 *)((u8 *)entity + (0x90))) -= bob_offset;
            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                ground_height = sample_terrain_surface_height(((S_80170DA8_0 *)motion)->unk_00.at02.v,
                    ((S_80170DA8_0 *)motion)->unk_04.at02.v,
                    (s16)(((S_80170DA8_2 *)entity_state)->unk_88 - 0x20));
                ground_delta = ground_height - ((S_80170DA8_2 *)entity_state)->unk_88;
                if (ground_delta < (*(s16 *)((u8 *)entity + (0x92)))) {
                    (*(s16 *)((u8 *)entity + (0x92))) = ground_delta;
                    (*(u8 *)((u8 *)entity + (0x9D))) = 0;
                    ((S_80170DA8_0 *)motion)->unk_14 = 0;
                    ((S_80170DA8_2 *)entity_state)->unk_1C.u |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                if (*(u8 **)&sprite->frameTable == D_801740E0) {
                    if (*(u16 *)&sprite->unk_04 == 0x100) {
                        (*(u16 *)((u8 *)entity + (0x9E))) = 0;
                    }
                    bob_tick = (*(u16 *)((u8 *)entity + (0x9E)))++;
                    signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = signed_tick * 0xE3;
                    (*(s32 *)((u8 *)entity + (0xA0))) = func_800644B8(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = hikewne_alt_direction_frames;
                        select_sprite_entry(sprite, hikewne_alt_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle
                            + ((S_80170DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                } else if (*(u8 **)&sprite->frameTable == hikewne_alt_direction_frames) {
                    bob_tick = (*(u16 *)((u8 *)entity + (0x9E)))++;
                    signed_tick = (s32)((u32)bob_tick << 16) >> 16;
                    bob_angle = signed_tick * 0xE3;
                    (*(s32 *)((u8 *)entity + (0xA0))) = func_800644B8(bob_angle) << 7;
                    if (*(u16 *)&sprite->unk_04 == 0x103) {
                        (sprite->frameTable) = D_801740E0;
                        select_sprite_entry(sprite, D_801740E0[((g_game_work.view.camera_rotation.parts.viewAngle
                            + ((S_80170DA8_2 *)entity_state)->unk_2A + 0x100) >> 9) & 7], 0);
                    }
                }
            }

            if (!((*(u16 *)((u8 *)entity + (0x98))) & 8)) {
                s32 height_adjust = -0x20;
                height_offset = (*(s16 *)((u8 *)entity + (0x92)));
                entity_flags = (*(u16 *)((u8 *)entity + (0x92)));
                if (height_adjust < height_offset) {
                    height_adjust = entity_flags - 8;
                    (*(s16 *)((u8 *)entity + (0x92))) = height_adjust;
                } else {
                    height_adjust = height_offset < -0x28;
                    if (height_adjust) {
                        height_adjust = entity_flags + 8;
                        (*(s16 *)((u8 *)entity + (0x92))) = height_adjust;
                    }
                }
            }
        }
    }

    entity_flags = ((S_80170DA8_2 *)entity_state)->unk_1C.u;
    if (entity_flags & 0x40000000) {
        ((S_80170DA8_2 *)entity_state)->unk_1C.u = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height(
            (sprite->unk_24 << 6) | 0x20,
            (sprite->unk_25 << 6) | 0x20,
            (s16)(((S_80170DA8_2 *)entity_state)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + (0x92))) =
                (((S_80170DA8_2 *)entity_state)->unk_88 - ground_height) +
                (*(u16 *)((u8 *)entity + (0x92)));
            ((S_80170DA8_2 *)entity_state)->unk_88 = ground_height;
        }
    }

    ((S_80170DA8_0 *)motion)->unk_0A = ((S_80170DA8_2 *)entity_state)->unk_88 +
        (*(u16 *)((u8 *)entity + (0x92))) - (*(u16 *)((u8 *)entity + (0xA2)));
    sprite->flags |= 0x40;
}
