#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void select_indirect_table_entry();
extern void func_800478B8();
extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern s32 D_8015F9DC;
extern u8 D_80162634[8];
extern u8 D_80162644[8];
extern u8 D_80162654[8];
extern u8 D_8016265C[8];
extern u8 D_80162664[8];
extern u8 D_8016266C[8];
extern Callback D_801626A0[];

typedef struct S_8015F3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8015F3A8_2;   /* base in update_entity_motion_facing_and_ground */

/* Run entity callbacks and update motion, facing, and ground height. */
void update_entity_motion_facing_and_ground(void *entity, EntityRec *motion, void *sprite)
{
    void *entity_base = entity;
    s16 old_state;
    void *call_entity;
    void *call_motion;
    void *call_sprite;
    s32 height_offset;
    s16 direction;
    s16 ground_height;
    s32 flags;
    s32 height_step;
    s32 state_check;
    s32 state_check_2;
    u16 initial_flags;
    u16 sprite_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *entry_entity = entity;
        Callback entry_callback;

        entry_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (entry_callback == (Callback)&D_8015F9DC) {
            entry_callback(entry_entity, motion, sprite, entry_entity);
            return;
        }
        (*(u8 *)((u8 *)entity + 0x71)) &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_sprite = sprite;
    old_state = (s8)((*(u8 *)((u8 *)entity + 0x6D)));
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_sprite, entity) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)entity + 0x8C));

        if (update_callback != 0) {
            update_callback(entity, motion, sprite, entity);
        }
    }
    D_801626A0[(*(u8 *)((u8 *)entity + 0x9A))](entity, motion, sprite, entity);
    {
        state_check = (u32)(u16)old_state << 16;
        state_check >>= 16;
        if (state_check != (*(s8 *)((u8 *)entity + 0x6D))) {
            try_move_actor_to_valid_position(entity, motion, sprite, entity);
            motion->x.v += motion->unk_0C;
            motion->y.v += motion->unk_10;
        } else {
            motion->x.v += motion->unk_0C;
            motion->y.v += motion->unk_10;
        }
    }

    if (!((*(s32 *)((u8 *)entity + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
        motion->flags14 += (*(s8 *)((u8 *)entity + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)entity + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)entity + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)entity + 0x90)) += motion->flags14;
    initial_flags = ((SpriteFrameState *)sprite)->flags;

    if (!(initial_flags & 0x8000)) {
        direction = ((g_game_work.view.viewAngle + ((S_8015F3A8_2 *)entity_base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction) {
            select_indirect_table_entry(sprite,
                *(u8 *)(*(u8 * *)&((SpriteFrameState *)sprite)->frameTable + direction),
                ((SpriteFrameState *)sprite)->unk_04);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        if (dir_sprite_flag[direction] != 0) {
            ((SpriteFrameState *)sprite)->flags |= 1;
        } else {
            ((SpriteFrameState *)sprite)->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(((S_8015F3A8_2 *)entity_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_8015F3A8_2 *)entity_base)->unk_1C & 0x20)) {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((SpriteFrameState *)sprite)->flags |= 0x7000;
            ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xFFFBFFFF;
        }

        ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;
        if (flags & 0x40000) {
            sprite_flags = ((SpriteFrameState *)sprite)->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *direction_frames = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (direction_frames == D_80162634) {
                    if (((SpriteFrameState *)sprite)->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)entity + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)entity + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)entity + 0xA4)) += (*(s32 *)((u8 *)entity + 0xAC));
                    (*(s32 *)((u8 *)entity + 0xAC)) += (*(s32 *)((u8 *)entity + 0xB0));
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames == D_80162644 || direction_frames == D_8016266C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames != D_80162654 && direction_frames != D_8016265C &&
                           direction_frames != D_80162664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            height_step = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_step == 0) {
                flags = (*(u16 *)((u8 *)entity + 0x92));
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                if (height_step >= height_offset) {
                    height_step = height_offset < -8;
                    if (height_step != 0) {
                        height_step = flags + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_step;
                    }
                } else {
                    height_step = flags - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_step;
                }
            }
        } else {
            state_check_2 = (*(s32 *)((u8 *)entity + 0xA4));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) += state_check_2;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(((S_8015F3A8_2 *)entity_base)->unk_88 - 0x20)) -
                                ((S_8015F3A8_2 *)entity_base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    ((S_8015F3A8_2 *)entity_base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_flags & 0x800) {
            ((SpriteFrameState *)sprite)->flags = initial_flags & 0x8FFF;
        } else {
            ((SpriteFrameState *)sprite)->flags = initial_flags | 0x7000;
        }
        ((S_8015F3A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;

        if (!(flags & 0x40000)) {
            s32 landing_step;

            landing_step = (*(s32 *)((u8 *)entity + 0xA4));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            (*(s32 *)((u8 *)entity + 0x90)) -= landing_step;
            if (!((*(u16 *)((u8 *)entity + 0x98)) & 8)) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(((S_8015F3A8_2 *)entity_base)->unk_88 - 0x20)) -
                                ((S_8015F3A8_2 *)entity_base)->unk_88;
                if (ground_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = ground_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    ((S_8015F3A8_2 *)entity_base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                u8 *direction_frames = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (direction_frames == D_80162634) {
                    (*(s32 *)((u8 *)entity + 0xAC)) = 0;
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                } else if (direction_frames == D_80162644 || direction_frames == D_8016266C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames != D_80162654 && direction_frames != D_8016265C &&
                           direction_frames != D_80162664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            height_step = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (height_step == 0) {
                flags = (*(u16 *)((u8 *)entity + 0x92));
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                if (height_step < height_offset) {
                    height_step = flags - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = height_step;
                } else {
                    height_step = height_offset < -8;
                    if (height_step != 0) {
                        height_step = flags + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = height_step;
                    }
                }
            }
        }
    }
    flags = ((S_8015F3A8_2 *)entity_base)->unk_1C;
    if (flags & 0x40000000) {
        ((S_8015F3A8_2 *)entity_base)->unk_1C = flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((((SpriteFrameState *)sprite)->unk_24 << 6) | 0x20,
                                      (((SpriteFrameState *)sprite)->unk_25 << 6) | 0x20,
                                      (s16)(((S_8015F3A8_2 *)entity_base)->unk_88 - 0x20));
        if (ground_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (u16)(*(s16 *)((u8 *)entity + 0x92)) +
                (((S_8015F3A8_2 *)entity_base)->unk_88 - ground_height);
            ((S_8015F3A8_2 *)entity_base)->unk_88 = ground_height;
        }
    }
    motion->z.w.i = ((S_8015F3A8_2 *)entity_base)->unk_88 +
                     (u16)(*(s16 *)((u8 *)entity + 0x92)) -
                     (*(u16 *)((u8 *)entity + 0xA6));
    ((SpriteFrameState *)sprite)->flags |= 0x40;
}
