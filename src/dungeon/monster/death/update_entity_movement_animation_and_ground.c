#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dir_step.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/monster/death.h"
#include "engine/texture.h"
#include "slus.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"
#include "dungeon/item.h"

typedef ActorActionHandler Callback;

extern s32 refresh_actor_facing_and_lifecycle();

extern s32 D_8014D9DC;
extern u8 D_80150634[8];
extern u8 D_80150644[8];
extern u8 D_80150654[8];
extern u8 D_8015065C[8];
extern u8 D_80150664[8];
extern u8 D_8015066C[8];
extern Callback D_801506A0[];

typedef struct S_8014D3A8_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_8014D3A8_2;   /* base in update_entity_movement_animation_and_ground */

/* Update entity callbacks, movement, animation, and ground height. */
/* Runs Death state callbacks from D_801506A0, updates sprite facing and height offsets, and resolves
 * ground contact. */
void update_entity_movement_animation_and_ground(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    S_8014D3A8_2 *entity_base = (S_8014D3A8_2 *)body;
    s16 old_state;
    void *call_entity;
    void *call_motion;
    void *call_sprite;
    s32 height_offset;
    s16 direction;
    s16 ground_height;
    s32 entity_flags;
    register s32 adjustment;
    u16 initial_sprite_flags;
    u16 sprite_flags;
    s32 adjusted_height;
    u16 height_flags;

    if (g_dungeon_status.flags & 0x2000) {
        void *entry_self = body;
        Callback entry_callback;

        entry_callback = body->unk_8C.handler;
        if (entry_callback == (Callback)&D_8014D9DC) {
            entry_callback(entry_self, motion, sprite, entry_self);
            return;
        }
        body->movement_queue_state &= 0x7F;
        return;
    }

    call_entity = body;
    call_motion = motion;
    call_sprite = sprite;
    old_state = (s8)((*((u8 *)body + 0x6D)));
    if (refresh_actor_facing_and_lifecycle(call_entity, call_motion, call_sprite, body) != 0) {
        return;
    }

    {
        Callback ordinary_callback = body->unk_8C.handler;

        if (ordinary_callback != 0) {
            ordinary_callback(body, motion, sprite, body);
        }
    }
    D_801506A0[body->action_id.u](body, motion, sprite, body);
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
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_base->unk_2A + 0x100) >> 9) & 7;
        if (body->unk_94 != direction) {
            select_indirect_table_entry(sprite,
                *(*(u8 * *)&sprite->frameTable + direction),
                sprite->unk_04);
            body->unk_94 = direction;
        }
        if (dir_sprite_flag[direction] != 0) {
            sprite->flags |= 1;
        } else {
            sprite->flags &= 0xFFFE;
        }
        apply_monster_koyaw_data(entity_base->unk_1C, (u8 *)sprite + 0xC);
        if (!(entity_base->unk_1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            entity_base->unk_1C &= 0xFFFBFFFF;
        }

        entity_base->unk_1C &= 0xF7FFFFFF;
        entity_flags = entity_base->unk_1C;
        if (entity_flags & 0x40000) {
            sprite_flags = sprite->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *frames = *(u8 * *)&sprite->frameTable;

                if (frames == D_80150634) {
                    if (sprite->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        (*(s32 *)((u8 *)body + 0xAC)) = 0x60000;
                        (*(s32 *)((u8 *)body + 0xB0)) = (s32)0xFFFF3000;
                    }
                    body->unk_A4.value += (*(s32 *)((u8 *)body + 0xAC));
                    (*(s32 *)((u8 *)body + 0xAC)) += (*(s32 *)((u8 *)body + 0xB0));
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frames == D_80150644 || frames == D_8015066C) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frames != D_80150654 && frames != D_8015065C &&
                           frames != D_80150664) {
                    body->unk_A4.value = 0;
                }
            }

            adjustment = body->action_state_flags & 8;
            if (adjustment == 0) {
                entity_flags = body->unk_90.parts.high.u;
                height_offset = body->unk_90.parts.high.s;
                if (adjustment < height_offset) {
                    adjustment = entity_flags - 8;
                    body->unk_90.parts.high.s = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = entity_flags + 8;
                        body->unk_90.parts.high.s = adjustment;
                    }
                }
            }
        } else {
            adjustment = body->unk_A4.value;
            adjusted_height = body->unk_90.value;
            height_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            adjusted_height += adjustment;
            height_offset = height_flags & 8;
            body->unk_90.value = adjusted_height;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(entity_base->unk_88 - 0x20)) -
                        entity_base->unk_88;
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = ground_height;
                    body->unk_9D.u = 0;
                    motion->velocity_z = 0;
                    entity_base->unk_1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_sprite_flags & 0x800) {
            sprite->flags = initial_sprite_flags & 0x8FFF;
        } else {
            sprite->flags = initial_sprite_flags | 0x7000;
        }
        entity_base->unk_1C &= 0xF7FFFFFF;
        entity_flags = entity_base->unk_1C;

        if (!(entity_flags & 0x40000)) {
            adjustment = body->unk_A4.value;
            adjusted_height = body->unk_90.value;
            height_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            adjusted_height -= adjustment;
            height_offset = height_flags & 8;
            body->unk_90.value = adjusted_height;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                      ((u16)motion->y.w.i),
                                      (s16)(entity_base->unk_88 - 0x20)) -
                        entity_base->unk_88;
                if (ground_height < body->unk_90.parts.high.s) {
                    body->unk_90.parts.high.s = ground_height;
                    body->unk_9D.u = 0;
                    motion->velocity_z = 0;
                    entity_base->unk_1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                u8 *frames = *(u8 * *)&sprite->frameTable;

                if (frames == D_80150634) {
                    (*(s32 *)((u8 *)body + 0xAC)) = 0;
                    body->unk_A4.value = 0;
                } else if (frames == D_80150644 || frames == D_8015066C) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frames != D_80150654 && frames != D_8015065C &&
                           frames != D_80150664) {
                    body->unk_A4.value = 0;
                }
            }

            adjustment = body->action_state_flags & 8;
            if (adjustment == 0) {
                height_offset = body->unk_90.parts.high.s;
                entity_flags = body->unk_90.parts.high.u;
                if (adjustment < height_offset) {
                    adjustment = entity_flags - 8;
                    body->unk_90.parts.high.s = adjustment;
                } else {
                    adjustment = height_offset < -8;
                    if (adjustment != 0) {
                        adjustment = entity_flags + 8;
                        body->unk_90.parts.high.s = adjustment;
                    }
                }
            }
        }
    }
    entity_flags = entity_base->unk_1C;
    if (entity_flags & 0x40000000) {
        entity_base->unk_1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                              (sprite->tile_y << 6) | 0x20,
                              (s16)(entity_base->unk_88 - 0x20));
        if (ground_height < 0x200) {
            body->unk_90.parts.high.s =
                (u16)body->unk_90.parts.high.s +
                (entity_base->unk_88 - ground_height);
            entity_base->unk_88 = ground_height;
        }
    }
    motion->z.w.i = entity_base->unk_88 +
                             (u16)body->unk_90.parts.high.s -
                             body->unk_A4.halves.high.u;
    sprite->flags |= 0x40;
}
