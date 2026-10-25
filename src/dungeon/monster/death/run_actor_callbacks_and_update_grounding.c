#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/texture.h"
#include "slus.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern void apply_monster_koyaw_data();
extern s32 refresh_actor_facing_and_lifecycle();
extern void try_move_actor_to_valid_position();
extern s16 sample_terrain_surface_height();

extern s32 D_8016B9DC;
extern u8 D_8016E634[8];
extern u8 D_8016E644[8];
extern u8 D_8016E654[8];
extern u8 D_8016E65C[8];
extern u8 D_8016E664[8];
extern u8 D_8016E66C[8];
extern Callback D_8016E6A0[];

typedef struct S_8016B3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8016B3A8_2;   /* base in run_actor_callbacks_and_update_grounding */

/* Runs actor callbacks and updates animation, movement, and ground height. */
/* Runs Death state callbacks from D_8016E6A0, updates sprite facing and height offsets, and resolves
 * ground contact. */
void run_actor_callbacks_and_update_grounding(void *self, ObjectPosition *motion, void *sprite)
{
    void *actor_base = self;
    s16 old_state;
    u8 old_state_byte;
    s32 height_offset;
    s16 height_offset_2;
    u16 height_bits;
    s16 direction;
    s16 floor_height;
    s32 actor_flags;
    register s32 adjustment;
    u16 initial_sprite_flags;
    u16 sprite_flags;
    s32 height_sum;
    u16 motion_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *callback_self = self;
        Callback special_callback;

        special_callback = (*(Callback *)((u8 *)self + 0x8C));
        if (special_callback == (Callback)&D_8016B9DC) {
            special_callback(callback_self, motion, sprite, callback_self);
            return;
        }
        (*(u8 *)((u8 *)self + 0x71)) &= 0x7F;
        return;
    }

    old_state_byte = (*(u8 *)((u8 *)self + 0x6D));
    old_state = (s8)old_state_byte;
    if (refresh_actor_facing_and_lifecycle(self, motion, sprite, self) != 0) {
        return;
    }

    {
        Callback update_callback = (*(Callback *)((u8 *)self + 0x8C));

        if (update_callback != 0) {
            update_callback(self, motion, sprite, self);
        }
    }
    D_8016E6A0[(*(u8 *)((u8 *)self + 0x9A))](self, motion, sprite, self);
    {
        s32 state_compare;

        state_compare = (u32)(u16)old_state << 16;
        state_compare >>= 16;
        if (state_compare != (*(s8 *)((u8 *)self + 0x6D))) {
            try_move_actor_to_valid_position(self, motion, sprite, self);
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        } else {
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        }
    }

    if (!((*(s32 *)((u8 *)self + 0x1C)) & 0x40000) &&
        !((*(u16 *)((u8 *)self + 0x98)) & 8)) {
        motion->velocity_z += (*(s8 *)((u8 *)self + 0x9D)) * 0x14000;
        (*(u8 *)((u8 *)self + 0x9D))++;
    } else {
        (*(u8 *)((u8 *)self + 0x9D)) = 0;
    }
    (*(s32 *)((u8 *)self + 0x90)) += motion->velocity_z;
    initial_sprite_flags = ((SpriteFrameState *)sprite)->flags;

    if (!(initial_sprite_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8016B3A8_2 *)actor_base)->unk_2A + 0x100) >> 9) & 7;
        if ((*(s16 *)((u8 *)self + 0x94)) != direction) {
            select_indirect_table_entry(sprite,
                *(u8 *)(*(u8 * *)&((SpriteFrameState *)sprite)->frameTable + direction),
                ((SpriteFrameState *)sprite)->unk_04);
            (*(s16 *)((u8 *)self + 0x94)) = direction;
        }
        {
            u32 flip_flags;

            if (dir_sprite_flag[direction] != 0) {
                flip_flags = ((SpriteFrameState *)sprite)->flags | 1;
            } else {
                flip_flags = ((SpriteFrameState *)sprite)->flags & 0xFFFE;
            }
            ((SpriteFrameState *)sprite)->flags = flip_flags;
        }
        apply_monster_koyaw_data(((S_8016B3A8_2 *)actor_base)->unk_1C, (u8 *)sprite + 0xC);
        if (!(((S_8016B3A8_2 *)actor_base)->unk_1C & 0x20)) {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            ((SpriteFrameState *)sprite)->flags |= 0x7000;
            ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xFFFBFFFF;
        }

        ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xF7FFFFFF;
        actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;
        if (actor_flags & 0x40000) {
            sprite_flags = ((SpriteFrameState *)sprite)->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *anim_table = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (anim_table == D_8016E634) {
                    if (((SpriteFrameState *)sprite)->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)self + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)self + 0xB0)) = (s32)0xFFFF3000;
                    }
                    (*(s32 *)((u8 *)self + 0xA4)) += (*(s32 *)((u8 *)self + 0xAC));
                    (*(s32 *)((u8 *)self + 0xAC)) += (*(s32 *)((u8 *)self + 0xB0));
                    if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)self + 0xA4)) = 0;
                    }
                } else if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
                    (*(s32 *)((u8 *)self + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)self + 0xA4)) = 0;
                    }
                } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                           anim_table != D_8016E664) {
                    (*(s32 *)((u8 *)self + 0xA4)) = 0;
                }
            }

            adjustment = (*(u16 *)((u8 *)self + 0x98)) & 8;
            if (adjustment == 0) {
                height_offset = (*(s16 *)((u8 *)self + 0x92));
                height_bits = (*(u16 *)((u8 *)self + 0x92));
                if (adjustment < height_offset) {
                    adjustment = height_bits - 8;
                    (*(s16 *)((u8 *)self + 0x92)) = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = height_bits + 8;
                        (*(s16 *)((u8 *)self + 0x92)) = adjustment;
                    }
                }
            }
        } else {

            adjustment = (*(s32 *)((u8 *)self + 0xA4));
            height_sum = (*(s32 *)((u8 *)self + 0x90));
            motion_flags = (*(u16 *)((u8 *)self + 0x98));
            (*(s16 *)((u8 *)self + 0xB8)) = 0;
            (*(s32 *)((u8 *)self + 0xA4)) = 0;
            height_sum += adjustment;
            (*(s32 *)((u8 *)self + 0x90)) = height_sum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(((S_8016B3A8_2 *)actor_base)->unk_88 - 0x20)) -
                        ((S_8016B3A8_2 *)actor_base)->unk_88;
                if (floor_height < (*(s16 *)((u8 *)self + 0x92))) {
                    (*(s16 *)((u8 *)self + 0x92)) = floor_height;
                    (*(u8 *)((u8 *)self + 0x9D)) = 0;
                    motion->velocity_z = 0;
                    ((S_8016B3A8_2 *)actor_base)->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_sprite_flags & 0x800) {
            ((SpriteFrameState *)sprite)->flags = initial_sprite_flags & 0x8FFF;
        } else {
            ((SpriteFrameState *)sprite)->flags = initial_sprite_flags | 0x7000;
        }
        ((S_8016B3A8_2 *)actor_base)->unk_1C &= 0xF7FFFFFF;
        actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;

        if (!(actor_flags & 0x40000)) {
            adjustment = (*(s32 *)((u8 *)self + 0xA4));
            height_sum = (*(s32 *)((u8 *)self + 0x90));
            motion_flags = (*(u16 *)((u8 *)self + 0x98));
            (*(s16 *)((u8 *)self + 0xB8)) = 0;
            (*(s32 *)((u8 *)self + 0xA4)) = 0;
            height_sum -= adjustment;
            (*(s32 *)((u8 *)self + 0x90)) = height_sum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(((S_8016B3A8_2 *)actor_base)->unk_88 - 0x20)) -
                        ((S_8016B3A8_2 *)actor_base)->unk_88;
                if (floor_height < (*(s16 *)((u8 *)self + 0x92))) {
                    (*(s16 *)((u8 *)self + 0x92)) = floor_height;
                    (*(u8 *)((u8 *)self + 0x9D)) = 0;
                    motion->velocity_z = 0;
                    ((S_8016B3A8_2 *)actor_base)->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(((SpriteFrameState *)sprite)->flags & 0x40)) {
                u8 *anim_table = *(u8 * *)&((SpriteFrameState *)sprite)->frameTable;

                if (anim_table == D_8016E634) {
                    (*(s32 *)((u8 *)self + 0xAC)) = 0;
                    (*(s32 *)((u8 *)self + 0xA4)) = 0;
                } else if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
                    (*(s32 *)((u8 *)self + 0xA4)) -= 0x40000;
                    if ((*(s32 *)((u8 *)self + 0xA4)) <= 0) {
                        (*(s32 *)((u8 *)self + 0xA4)) = 0;
                    }
                } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                           anim_table != D_8016E664) {
                    (*(s32 *)((u8 *)self + 0xA4)) = 0;
                }
            }

            adjustment = (*(u16 *)((u8 *)self + 0x98)) & 8;
            if (adjustment == 0) {
                height_offset_2 = (*(s16 *)((u8 *)self + 0x92));
                height_bits = (*(u16 *)((u8 *)self + 0x92));
                if (adjustment < height_offset_2) {
                    adjustment = height_bits - 8;
                    (*(s16 *)((u8 *)self + 0x92)) = adjustment;
                } else {
                    adjustment = height_offset_2 < -8;
                    if (adjustment != 0) {
                        adjustment = height_bits + 8;
                        (*(s16 *)((u8 *)self + 0x92)) = adjustment;
                    }
                }
            }
        }
    }
    actor_flags = ((S_8016B3A8_2 *)actor_base)->unk_1C;
    if (actor_flags & 0x40000000) {
        ((S_8016B3A8_2 *)actor_base)->unk_1C = actor_flags & 0xBFFFFFFF;
        floor_height = sample_terrain_surface_height((((SpriteFrameState *)sprite)->tile_x << 6) | 0x20,
                              (((SpriteFrameState *)sprite)->tile_y << 6) | 0x20,
                              (s16)(((S_8016B3A8_2 *)actor_base)->unk_88 - 0x20));
        if (floor_height < 0x200) {
            (*(s16 *)((u8 *)self + 0x92)) =
                (u16)(*(s16 *)((u8 *)self + 0x92)) +
                (((S_8016B3A8_2 *)actor_base)->unk_88 - floor_height);
            ((S_8016B3A8_2 *)actor_base)->unk_88 = floor_height;
        }
    }
    motion->z.w.i = ((S_8016B3A8_2 *)actor_base)->unk_88 +
                             (u16)(*(s16 *)((u8 *)self + 0x92)) -
                             (*(u16 *)((u8 *)self + 0xA6));
    ((SpriteFrameState *)sprite)->flags |= 0x40;
}
