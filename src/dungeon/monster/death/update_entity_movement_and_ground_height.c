#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/texture.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void apply_monster_koyaw_data(s32 flags, s8 *dst);
extern s32 refresh_actor_facing_and_lifecycle();

extern s32 death_action_resume_address;
extern u8 death_direction_frames[8];
extern u8 death_frame_set_7[8];
extern u8 death_frame_set_4[8];
extern u8 death_frame_set_5[8];
extern u8 death_frame_set_6[8];
extern u8 death_frame_set[8];
extern Callback D_801746A0[];

typedef struct S_801713A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801713A8_2;   /* base in update_entity_movement_and_ground_height */

/* Update entity callbacks, movement, sprite direction, and ground-relative height. */
/* Runs Death state callbacks from D_801746A0, updates sprite facing and height offsets, and resolves
 * ground contact. */
void update_entity_movement_and_ground_height(void *entity, ObjectPosition *motion, void *sprite)
{
    S_801713A8_2 *entity_base = entity;
    s16 old_state;
    u8 old_state_byte;
    s32 height_offset;
    s32 height_offset_2;
    u16 height_bits;
    s16 direction;
    s16 ground_height;
    s32 entity_flags;
    s32 height_work;
    u16 initial_flags;
    u16 sprite_flags;
    s32 height_accum;
    u16 motion_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *entry_entity = entity;
        Callback entry_callback;

        entry_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (entry_callback == (Callback)&death_action_resume_address) {
            entry_callback(entry_entity, motion, sprite, entry_entity);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    old_state_byte = (*(u8 *)((u8 *)entity + 0x6D));
    old_state = (s8)old_state_byte;
    if (refresh_actor_facing_and_lifecycle(entity, motion, sprite, entity) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + 0x8C));

        if (update_callback != 0) {
            update_callback(entity, motion, sprite, entity);
        }
    }
    D_801746A0[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    {
        s32 state_compare;

        state_compare = (u32)(u16)old_state << 16;
        state_compare >>= 16;
        if (state_compare != (*(s8 *)((u8 *)entity + 0x6D))) {
            try_move_actor_to_valid_position(entity, motion, sprite, entity);
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        } else {
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        }
    }

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->velocity_z += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->velocity_z;
    initial_flags = ((SpriteFrameState *)sprite)->flags;

    if (!(initial_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_base->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction) {
            select_indirect_table_entry(sprite,
                *(u8 *)(*(u8 * *)&((SpriteFrameState *)sprite)->frameTable + direction),
                ((SpriteFrameState *)sprite)->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        {
            u32 facing_flags;

            if (dir_sprite_flag[direction] != 0) {
                facing_flags = ((SpriteFrameState *)sprite)->flags | 1;
            } else {
                facing_flags = ((SpriteFrameState *)sprite)->flags & 0xFFFE;
            }
            ((SpriteFrameState *)sprite)->flags = facing_flags;
        }
        apply_monster_koyaw_data(entity_base->unk_1C, (u8 *)sprite + 0xC);
        if (!(entity_base->unk_1C & 0x20)) {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            ((SpriteFrameState *)sprite)->flags |= 0x7000;
            entity_base->unk_1C &= 0xFFFBFFFF;
        }

        entity_base->unk_1C &= 0xF7FFFFFF;
        entity_flags = entity_base->unk_1C;
        if (entity_flags & 0x40000) {
            sprite_flags = ((SpriteFrameState *)sprite)->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *frame_table = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (frame_table == death_direction_frames) {
                    if (((SpriteFrameState *)sprite)->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)entity + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)entity + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)entity + 0xA4)) += (*(s32 *)((u8 *)entity + 0xAC));
                    (*(s32 *)((u8 *)entity + 0xAC)) += (*(s32 *)((u8 *)entity + 0xB0));
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (frame_table == death_frame_set_7 || frame_table == death_frame_set) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (frame_table != death_frame_set_4 && frame_table != death_frame_set_5 &&
                           frame_table != death_frame_set_6) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            height_work = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_work == 0) {
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_work < height_offset) {
                    height_work = height_bits - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_work;
                } else {
                    height_work = height_offset < -8;
                    if (height_work != 0) {
                        height_work = height_bits + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_work;
                    }
                }
            }
        } else {
            height_work = (*(s32 *)((u8 *)entity + 0xA4));
            height_accum = (*(s32 *)((u8 *)entity + 0x90));
            motion_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_accum += height_work;
            (*(s32 *)((u8 *)entity + 0x90)) = height_accum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(entity_base->unk_88 - 0x20)) -
                            entity_base->unk_88;
                if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->velocity_z = 0;
                    entity_base->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_flags & 0x800) {
            ((SpriteFrameState *)sprite)->flags = initial_flags & 0x8FFF;
        } else {
            ((SpriteFrameState *)sprite)->flags = initial_flags | 0x7000;
        }
        entity_base->unk_1C &= 0xF7FFFFFF;
        entity_flags = entity_base->unk_1C;

        if (!(entity_flags & 0x40000)) {
            height_work = (*(s32 *)((u8 *)entity + 0xA4));
            height_accum = (*(s32 *)((u8 *)entity + 0x90));
            motion_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_accum -= height_work;
            (*(s32 *)((u8 *)entity + 0x90)) = height_accum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(entity_base->unk_88 - 0x20)) -
                            entity_base->unk_88;
                if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->velocity_z = 0;
                    entity_base->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                u8 *frame_table = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (frame_table == death_direction_frames) {
                    (*(s32 *)((u8 *)entity + 0xAC)) = 0;
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                } else if (frame_table == death_frame_set_7 || frame_table == death_frame_set) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (frame_table != death_frame_set_4 && frame_table != death_frame_set_5 &&
                           frame_table != death_frame_set_6) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            height_work = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_work == 0) {
                height_offset_2 = (*(s16 *)((u8 *)entity + 0x92));
                height_bits = (*(u16 *)((u8 *)entity + 0x92));
                if (height_work < height_offset_2) {
                    height_work = height_bits - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_work;
                } else {
                    height_work = height_offset_2 < -8;
                    if (height_work != 0) {
                        height_work = height_bits + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_work;
                    }
                }
            }
        }
    }
    entity_flags = entity_base->unk_1C;
    if (entity_flags & 0x40000000) {
        entity_base->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((((SpriteFrameState *)sprite)->tile_x << 6) | 0x20,
                              (((SpriteFrameState *)sprite)->tile_y << 6) | 0x20,
                              (s16)(entity_base->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (u16)(*(s16 *)((u8 *)entity + 0x92)) +
                (entity_base->unk_88 - ground_height);
            entity_base->unk_88 = ground_height;
        }
    }
    motion->z.w.i = entity_base->unk_88 +
                             (u16)(*(s16 *)((u8 *)entity + 0x92)) -
                             (*(u16 *)((u8 *)entity + 0xA6));
    ((SpriteFrameState *)sprite)->flags |= 0x40;
}
