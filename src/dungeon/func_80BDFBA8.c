#include "common.h"
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

extern s32 D_801539DC;
extern u8 D_80156634[8];
extern u8 D_80156644[8];
extern u8 D_80156654[8];
extern u8 D_8015665C[8];
extern u8 D_80156664[8];
extern u8 D_8015666C[8];
extern Callback D_801566A0[];


typedef struct S_801533A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_801533A8_2;   /* base in update_actor_animation_movement */

/* Updates entity callbacks, animation, movement, and floor height. */
void update_actor_animation_movement(void *entity, EntityRec *motion, void *sprite)
{
    void *entity_base = entity;
    s16 old_state;
    void *call_entity;
    void *call_motion;
    void *call_sprite;
    s32 height_offset;
    s16 direction;
    s16 floor_height;
    s32 entity_flags;
    register s32 adjustment;
    u16 initial_sprite_flags;
    u16 sprite_flags;
    s32 height_fixed;
    u16 height_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *callback_entity = entity;
        Callback special_callback;

        special_callback = (*(Callback *)((u8 *)entity + 0x8C));
        if (special_callback == (Callback)&D_801539DC) {
            special_callback(callback_entity, motion, sprite, callback_entity);
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
    D_801566A0[((u8 *)entity)[154]](entity, motion, sprite, entity);
    {
        s32 previous_state;

        previous_state = (u32)(u16)old_state << 16;
        previous_state >>= 16;
        if (previous_state != (*(s8 *)((u8 *)entity + 0x6D))) {
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
    initial_sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;

    if (!(initial_sprite_flags & 0x8000)) {
        direction = ((g_game_work.view.viewAngle + ((S_801533A8_2 *)entity_base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)entity + 0x94)) != direction) {
            select_indirect_table_entry(sprite,
                *(u8 *)(((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 + direction),
                ((Rec_D_80082E80 *)sprite)->unk_04.as_s8);
            (*(s16 *)((u8 *)entity + 0x94)) = direction;
        }
        if (dir_sprite_flag[direction] != 0) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 1;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v &= 0xFFFE;
        }
        apply_monster_koyaw_data(((S_801533A8_2 *)entity_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_801533A8_2 *)entity_base)->unk_1C & 0x20)) {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                func_800478B8(sprite);
            }
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x7000;
            ((S_801533A8_2 *)entity_base)->unk_1C &= 0xFFFBFFFF;
        }

        ((S_801533A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        entity_flags = ((S_801533A8_2 *)entity_base)->unk_1C;
        if (entity_flags & 0x40000) {
            sprite_flags = ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v;
            if (!(sprite_flags & 0x40)) {
                u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

                if (direction_frames == D_80156634) {
                    if (((Rec_D_80082E80 *)sprite)->unk_04.as_s8 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)entity + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)entity + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)entity + 0xA4)) += (*(s32 *)((u8 *)entity + 0xAC));
                    (*(s32 *)((u8 *)entity + 0xAC)) += (*(s32 *)((u8 *)entity + 0xB0));
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames == D_80156644 || direction_frames == D_8015666C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames != D_80156654 && direction_frames != D_8015665C &&
                           direction_frames != D_80156664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            adjustment = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (adjustment == 0) {
                entity_flags = (*(u16 *)((u8 *)entity + 0x92));
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                if (adjustment < height_offset) {
                    adjustment = entity_flags - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = entity_flags + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = adjustment;
                    }
                }
            }
        } else {

            adjustment = (*(s32 *)((u8 *)entity + 0xA4));
            height_fixed = (*(s32 *)((u8 *)entity + 0x90));
            height_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_fixed += adjustment;
            (*(s32 *)((u8 *)entity + 0x90)) = height_fixed;
            height_offset = height_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(((S_801533A8_2 *)entity_base)->unk_88 - 0x20)) -
                        ((S_801533A8_2 *)entity_base)->unk_88;
                if (floor_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    ((S_801533A8_2 *)entity_base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_sprite_flags & 0x800) {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags & 0x8FFF;
        } else {
            ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v = initial_sprite_flags | 0x7000;
        }
        ((S_801533A8_2 *)entity_base)->unk_1C &= 0xF7FFFFFF;
        entity_flags = ((S_801533A8_2 *)entity_base)->unk_1C;

        if (!(entity_flags & 0x40000)) {
            adjustment = (*(s32 *)((u8 *)entity + 0xA4));
            height_fixed = (*(s32 *)((u8 *)entity + 0x90));
            height_flags = (*(u16 *)((u8 *)entity + 0x98));
            (*(s16 *)((u8 *)entity + 0xB8)) = 0;
            (*(s32 *)((u8 *)entity + 0xA4)) = 0;
            height_fixed -= adjustment;
            (*(s32 *)((u8 *)entity + 0x90)) = height_fixed;
            height_offset = height_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(((S_801533A8_2 *)entity_base)->unk_88 - 0x20)) -
                        ((S_801533A8_2 *)entity_base)->unk_88;
                if (floor_height < (*(s16 *)((u8 *)entity + 0x92))) {
                    (*(s16 *)((u8 *)entity + 0x92)) = floor_height;
                    (*(u8 *)((u8 *)entity + 0x9D)) = 0;
                    motion->flags14 = 0;
                    ((S_801533A8_2 *)entity_base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x40)) {
                u8 *direction_frames = ((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8;

                if (direction_frames == D_80156634) {
                    (*(s32 *)((u8 *)entity + 0xAC)) = 0;
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                } else if (direction_frames == D_80156644 || direction_frames == D_8015666C) {
                    (*(s32 *)((u8 *)entity + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)entity + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                    }
                } else if (direction_frames != D_80156654 && direction_frames != D_8015665C &&
                           direction_frames != D_80156664) {
                    (*(s32 *)((u8 *)entity + 0xA4)) = 0;
                }
            }

            adjustment = (*(u16 *)((u8 *)entity + 0x98)) & 8;
            if (adjustment == 0) {
                height_offset = (*(s16 *)((u8 *)entity + 0x92));
                entity_flags = (*(u16 *)((u8 *)entity + 0x92));
                if (adjustment < height_offset) {
                    adjustment = entity_flags - 8;
                    (*(s16 *)((u8 *)entity + 0x92)) = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = entity_flags + 8;
                        (*(s16 *)((u8 *)entity + 0x92)) = adjustment;
                    }
                }
            }
        }
    }
    entity_flags = ((S_801533A8_2 *)entity_base)->unk_1C;
    if (entity_flags & 0x40000000) {
        ((S_801533A8_2 *)entity_base)->unk_1C = entity_flags & 0xBFFFFFFF;
        floor_height = sample_terrain_surface_height((((Rec_D_80082E80 *)sprite)->unk_24 << 6) | 0x20,
                              (((Rec_D_80082E80 *)sprite)->unk_25 << 6) | 0x20,
                              (s16)(((S_801533A8_2 *)entity_base)->unk_88 - 0x20));
        if (floor_height < 0x200) {
            (*(s16 *)((u8 *)entity + 0x92)) =
                (u16)(*(s16 *)((u8 *)entity + 0x92)) +
                (((S_801533A8_2 *)entity_base)->unk_88 - floor_height);
            ((S_801533A8_2 *)entity_base)->unk_88 = floor_height;
        }
    }
    motion->z.w.i = ((S_801533A8_2 *)entity_base)->unk_88 +
                             (u16)(*(s16 *)((u8 *)entity + 0x92)) -
                             (*(u16 *)((u8 *)entity + 0xA6));
    ((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v |= 0x40;
}
