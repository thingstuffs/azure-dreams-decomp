#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

extern void apply_monster_koyaw_data(void *, void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void advance_sprite_animation_and_textures(void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 get_entity_effect_value(void *, s32);

extern s8 view_direction_depth_biases[];
extern u8 uboat_ready_frames[];
extern u8 D_800E2400[];
extern u8 D_800E2408[];
extern u8 D_800E2420[];
extern u8 uboat_action_frames[];
extern u8 uboat_aura_start_frames[];
extern u8 uboat_aura_later_frames[];
extern u8 D_800E2450[];
extern u8 uboat_timed_motion_frames[];
extern u8 uboat_timed_motion_frames_alt[];

#define PTR(base, off) (*(u8 **)((u8 *)(base) + (off)))
#define S16(base, off) (*(s16 *)((u8 *)(base) + (off)))
#define U16(base, off) (*(u16 *)((u8 *)(base) + (off)))
#define U8(base, off) (*(u8 *)((u8 *)(base) + (off)))

/* Updates entity appearance, position, and facing from its owner and effect state. */
void update_entity_from_owner_effect(void *owner_data, void *position_data, u8 *entity)
{
    u8 *record;
    u8 *effect;
    u8 *appearance;
    u8 *coords;
    void *effect_data;
    GameWork *angle_table;

    s32 facing_check;
    u8 *saved_effect;
    void *appearance_type;
    s32 direction_index;
    s32 angle_sector;
    s16 effect_angle;

    record = PTR(((u8 *)(owner_data)), 0xAC);
    effect = record + 0x20;
    effect_data = PTR(effect, 0x1C);
    appearance = PTR(record, 0xC);
    coords = PTR(record, 8);

    apply_monster_koyaw_data(effect_data, entity + 0xC);

    saved_effect = effect;
    if ((*(u32 *)(effect + 0x1C) & 0x20) == 0) {
        advance_sprite_animation_and_textures(entity);
    }

    if (PTR(appearance, 0x2C) == D_800E2400) {
        advance_sprite_animation_and_textures(entity);
        advance_sprite_animation_and_textures(entity);
    }

    facing_check = U16(effect, 0x2A);
    effect_angle = S16(effect, 0x2A);
    if (S16(((u8 *)(owner_data)), 0x2A) != effect_angle) {
        U16(((u8 *)(owner_data)), 0x2A) = facing_check;
        select_sprite_entry(
            entity,
            PTR(entity, 0x2C)[(g_game_work.view.camera_rotation.parts.viewAngle + effect_angle + 0x100) >> 9 & 7],
            0);
    }

    angle_table = &g_game_work;
    angle_sector =
        (angle_table->view.camera_rotation.parts.viewAngle + S16(((u8 *)(owner_data)), 0x2A) + 0x100) >> 9;
    {
        u8 sector_check;
        direction_index = angle_sector & 7;
        sector_check = direction_index;

        angle_sector = S16(((u8 *)(owner_data)), 0x94);
        if (angle_sector != sector_check) {
            select_sprite_entry(entity, PTR(entity, 0x2C)[sector_check], 0);
            S16(((u8 *)(owner_data)), 0x94) = direction_index;
        }
    }

    U16(entity, 0x14) = U16(appearance, 0x14);
    U16(position_data, 2) = U16(coords, 2);
    U16(position_data, 6) = U16(coords, 6);
    U16(position_data, 0xA) = U16(coords, 0xA);

    direction_index =
        (angle_table->view.camera_rotation.parts.viewAngle + S16(((u8 *)(owner_data)), 0x2A) + 0x100) >> 9 & 7;
    S16(entity, 6) = (s32)view_direction_depth_biases[(u8)direction_index] * 4;
    U16(entity, 0x1C) = U16(appearance, 0x1C);
    U16(entity, 0x1E) = U16(appearance, 0x1E);
    U16(entity, 0x12) = U16(appearance, 0x12);

    if ((U16(record, 0x1E) & 0x8000) == 0) {
        appearance_type = PTR(appearance, 0x2C);
        if (appearance_type == uboat_ready_frames ||
            appearance_type == D_800E2408 ||
            appearance_type == D_800E2420 ||
            appearance_type == uboat_action_frames ||
            appearance_type == D_800E2450 ||
            appearance_type == uboat_timed_motion_frames ||
            appearance_type == uboat_timed_motion_frames_alt ||
            appearance_type == uboat_aura_later_frames ||
            appearance_type == uboat_aura_start_frames) {
            U16(((u8 *)(owner_data)), -2) |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            U8(saved_effect, 0xB0)--;
            return;
        }
        if ((get_entity_effect_value(effect, STATUS_FROG) << 16) == 0) {
            return;
        }
    }

    U16(((u8 *)(owner_data)), -2) |= 0x8000;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
