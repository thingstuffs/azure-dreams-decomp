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
#include "dungeon/item.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle();

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
void run_actor_callbacks_and_update_grounding(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_8016B3A8_2 *actor_base = (S_8016B3A8_2 *)body;
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
        void *callback_self = body;
        ActorActionHandler special_callback;

        special_callback = body->unk_8C.handler;
        if (special_callback == (ActorActionHandler)&D_8016B9DC) {
            special_callback(callback_self, motion, sprite, callback_self);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }

    old_state_byte = (*((u8 *)body + 0x6D));
    old_state = (s8)old_state_byte;
    if (refresh_actor_facing_and_lifecycle(body, motion, sprite, body) != 0) {
        return;
    }

    {
        ActorActionHandler update_callback = body->unk_8C.handler;

        if (update_callback != 0) {
            update_callback(body, motion, sprite, body);
        }
    }
    D_8016E6A0[body->action_id.u](body, motion, sprite, body);
    {
        s32 state_compare;

        state_compare = (u32)(u16)old_state << 16;
        state_compare >>= 16;
        if (state_compare != body->pending_turn_updates) {
            try_move_actor_to_valid_position(body, motion, sprite, body);
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        } else {
            motion->x.v += motion->velocity_x;
            motion->y.v += motion->velocity_y;
        }
    }

    if (!(body->flags1C & 0x40000) &&
        !(body->action_state_flags & 8)) {
        motion->velocity_z += body->unk_9D.s * 0x14000;
        body->unk_9D.u++;
    } else {
        body->unk_9D.u = 0;
    }
    body->unk_90.value += motion->velocity_z;
    initial_sprite_flags = sprite->flags;

    if (!(initial_sprite_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_base->unk_2A + 0x100) >> 9) & 7;
        if (body->unk_94 != direction) {
            select_indirect_table_entry(sprite,
                *(*(u8 * *)&sprite->frameTable + direction),
                sprite->unk_04);
            body->unk_94 = direction;
        }
        {
            u32 flip_flags;

            if (dir_sprite_flag[direction] != 0) {
                flip_flags = sprite->flags | 1;
            } else {
                flip_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = flip_flags;
        }
        apply_monster_koyaw_data(actor_base->unk_1C, (u8 *)sprite + 0xC);
        if (!(actor_base->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            actor_base->unk_1C &= 0xFFFBFFFF;
        }

        actor_base->unk_1C &= 0xF7FFFFFF;
        actor_flags = actor_base->unk_1C;
        if (actor_flags & 0x40000) {
            sprite_flags = sprite->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *anim_table = *(u8 * *)&sprite->frameTable;

                if (anim_table == D_8016E634) {
                    if (sprite->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)body + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)body + 0xB0)) = (s32)0xFFFF3000;
                    }
                    body->unk_A4.value += (*(s32 *)((u8 *)body + 0xAC));
                    (*(s32 *)((u8 *)body + 0xAC)) += (*(s32 *)((u8 *)body + 0xB0));
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                           anim_table != D_8016E664) {
                    body->unk_A4.value = 0;
                }
            }

            adjustment = body->action_state_flags & 8;
            if (adjustment == 0) {
                height_offset = body->unk_90.parts.high.s;
                height_bits = body->unk_90.parts.high.u;
                if (adjustment < height_offset) {
                    adjustment = height_bits - 8;
                    body->unk_90.parts.high.s = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = height_bits + 8;
                        body->unk_90.parts.high.s = adjustment;
                    }
                }
            }
        } else {

            adjustment = body->unk_A4.value;
            height_sum = body->unk_90.value;
            motion_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            height_sum += adjustment;
            body->unk_90.value = height_sum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                if (floor_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = floor_height;
                    body->unk_9D.u = 0;
                    motion->velocity_z = 0;
                    actor_base->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_sprite_flags & 0x800) {
            sprite->flags = initial_sprite_flags & 0x8FFF;
        } else {
            sprite->flags = initial_sprite_flags | 0x7000;
        }
        actor_base->unk_1C &= 0xF7FFFFFF;
        actor_flags = actor_base->unk_1C;

        if (!(actor_flags & 0x40000)) {
            adjustment = body->unk_A4.value;
            height_sum = body->unk_90.value;
            motion_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            height_sum -= adjustment;
            body->unk_90.value = height_sum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                floor_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(actor_base->unk_88 - 0x20)) -
                        actor_base->unk_88;
                if (floor_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = floor_height;
                    body->unk_9D.u = 0;
                    motion->velocity_z = 0;
                    actor_base->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                u8 *anim_table = *(u8 * *)&sprite->frameTable;

                if (anim_table == D_8016E634) {
                    (*(s32 *)((u8 *)body + 0xAC)) = 0;
                    body->unk_A4.value = 0;
                } else if (anim_table == D_8016E644 || anim_table == D_8016E66C) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (anim_table != D_8016E654 && anim_table != D_8016E65C &&
                           anim_table != D_8016E664) {
                    body->unk_A4.value = 0;
                }
            }

            adjustment = body->action_state_flags & 8;
            if (adjustment == 0) {
                height_offset_2 = body->unk_90.parts.high.s;
                height_bits = body->unk_90.parts.high.u;
                if (adjustment < height_offset_2) {
                    adjustment = height_bits - 8;
                    body->unk_90.parts.high.s = adjustment;
                } else {
                    adjustment = height_offset_2 < -8;
                    if (adjustment != 0) {
                        adjustment = height_bits + 8;
                        body->unk_90.parts.high.s = adjustment;
                    }
                }
            }
        }
    }
    actor_flags = actor_base->unk_1C;
    if (actor_flags & 0x40000000) {
        actor_base->unk_1C = actor_flags & 0xBFFFFFFF;
        floor_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                              (sprite->tile_y << 6) | 0x20,
                              (s16)(actor_base->unk_88 - 0x20));
        if (floor_height < 0x200) {
            body->unk_90.parts.high.s =
                (u16)body->unk_90.parts.high.s +
                (actor_base->unk_88 - floor_height);
            actor_base->unk_88 = floor_height;
        }
    }
    motion->z.w.i = actor_base->unk_88 +
                             (u16)body->unk_90.parts.high.s -
                             body->unk_A4.halves.high.u;
    sprite->flags |= 0x40;
}
