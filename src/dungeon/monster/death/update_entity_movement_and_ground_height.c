#include "common.h"
#include "dungeon/monster/death/actor_status_flags_g00165.h"
#include "dungeon/monster/death.h"
#include "dungeon/monster/death_frames.h"
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
#include "dungeon/data.h"

typedef void (*Callback)(void *, void *, void *, void *);

extern s32 refresh_actor_facing_and_lifecycle();

extern Callback D_801746A0[];


/* Update entity callbacks, movement, sprite direction, and ground-relative height. */
/* Runs Death state callbacks from D_801746A0, updates sprite facing and height offsets, and resolves
 * ground contact. */
void update_entity_movement_and_ground_height(ActorRecord *body, ObjectPosition *motion, SpriteFrameState *sprite)
{
    ActorRecord *entity_base = body;
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
        void *entry_entity = body;
        ActorActionHandler entry_callback;

        entry_callback = body->unk_8C.handler;
        if (entry_callback == (ActorActionHandler)&death_action_resume_address) {
            entry_callback(entry_entity, motion, sprite, entry_entity);
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
    D_801746A0[body->action_id](body, motion, sprite, body);
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
        motion->velocity_z += (body->unk_9D) * 0x14000;
        body->unk_9D++;
    } else {
        body->unk_9D = 0;
    }
    body->unk_90.value += motion->velocity_z;
    initial_flags = sprite->flags;

    if (!(initial_flags & 0x8000)) {
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_base->facing + 0x100) >> 9) & 7;
        if (body->unk_94 != direction) {
            select_indirect_table_entry(sprite,
                *(*(u8 * *)&sprite->frameTable + direction),
                sprite->unk_04);
            body->unk_94 = direction;
        }
        {
            u32 facing_flags;

            if (dir_sprite_flag[direction] != 0) {
                facing_flags = sprite->flags | 1;
            } else {
                facing_flags = sprite->flags & 0xFFFE;
            }
            sprite->flags = facing_flags;
        }
        apply_monster_koyaw_data(entity_base->flags1C, (u8 *)sprite + 0xC);
        if (!(entity_base->flags1C & 0x20)) {
            if (!(sprite->flags & 0x40)) {
                advance_sprite_animation_and_textures(sprite);
            }
        } else {
            sprite->flags |= 0x7000;
            entity_base->flags1C &= 0xFFFBFFFF;
        }

        entity_base->flags1C &= 0xF7FFFFFF;
        entity_flags = entity_base->flags1C;
        if (entity_flags & 0x40000) {
            sprite_flags = sprite->flags;
            if (!(sprite_flags & 0x40)) {
                u8 *frame_table = *(u8 * *)&sprite->frameTable;

                if (frame_table == death_direction_frames) {
                    if (sprite->unk_04 == 3 && (sprite_flags & 0x1000)) {
                        body->unk_AC.value = 0x60000;
                        body->unk_B0.value = (s32)0xFFFF3000;
                    }
                    body->unk_A4.value += body->unk_AC.value;
                    body->unk_AC.value += body->unk_B0.value;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frame_table == death_frame_set_7 || frame_table == death_frame_set) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frame_table != death_frame_set_4 && frame_table != death_frame_set_5 &&
                           frame_table != death_frame_set_6) {
                    body->unk_A4.value = 0;
                }
            }

            height_work = body->action_state_flags & 8;
            if (height_work == 0) {
                height_offset = body->unk_90.parts.high;
                height_bits = body->unk_90.parts.high;
                if (height_work < height_offset) {
                    height_work = height_bits - 8;
                    body->unk_90.parts.high = height_work;
                } else {
                    height_work = height_offset < -8;
                    if (height_work != 0) {
                        height_work = height_bits + 8;
                        body->unk_90.parts.high = height_work;
                    }
                }
            }
        } else {
            height_work = body->unk_A4.value;
            height_accum = body->unk_90.value;
            motion_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            height_accum += height_work;
            body->unk_90.value = height_accum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(entity_base->ground_height - 0x20)) -
                            entity_base->ground_height;
                if (ground_height < body->unk_90.parts.high) {
                    body->unk_90.parts.high = ground_height;
                    body->unk_9D = 0;
                    motion->velocity_z = 0;
                    entity_base->flags1C |= 0x08000000;
                }
            }
        }
    } else {
        if (initial_flags & 0x800) {
            sprite->flags = initial_flags & 0x8FFF;
        } else {
            sprite->flags = initial_flags | 0x7000;
        }
        entity_base->flags1C &= 0xF7FFFFFF;
        entity_flags = entity_base->flags1C;

        if (!(entity_flags & 0x40000)) {
            height_work = body->unk_A4.value;
            height_accum = body->unk_90.value;
            motion_flags = body->action_state_flags;
            (*(s16 *)((u8 *)body + 0xB8)) = 0;
            body->unk_A4.value = 0;
            height_accum -= height_work;
            body->unk_90.value = height_accum;
            height_offset = motion_flags & 8;
            if (height_offset == 0) {
                ground_height = sample_terrain_surface_height(((u16)motion->x.w.i),
                                              ((u16)motion->y.w.i),
                                              (s16)(entity_base->ground_height - 0x20)) -
                            entity_base->ground_height;
                if (ground_height < body->unk_90.parts.high) {
                    body->unk_90.parts.high = ground_height;
                    body->unk_9D = 0;
                    motion->velocity_z = 0;
                    entity_base->flags1C |= 0x08000000;
                }
            }
        } else {
            if (!(sprite->flags & 0x40)) {
                u8 *frame_table = *(u8 * *)&sprite->frameTable;

                if (frame_table == death_direction_frames) {
                    body->unk_AC.value = 0;
                    body->unk_A4.value = 0;
                } else if (frame_table == death_frame_set_7 || frame_table == death_frame_set) {
                    body->unk_A4.value -= 0x40000;
                    if (body->unk_A4.value <= 0) {
                        body->unk_A4.value = 0;
                    }
                } else if (frame_table != death_frame_set_4 && frame_table != death_frame_set_5 &&
                           frame_table != death_frame_set_6) {
                    body->unk_A4.value = 0;
                }
            }

            height_work = body->action_state_flags & 8;
            if (height_work == 0) {
                height_offset_2 = body->unk_90.parts.high;
                height_bits = body->unk_90.parts.high;
                if (height_work < height_offset_2) {
                    height_work = height_bits - 8;
                    body->unk_90.parts.high = height_work;
                } else {
                    height_work = height_offset_2 < -8;
                    if (height_work != 0) {
                        height_work = height_bits + 8;
                        body->unk_90.parts.high = height_work;
                    }
                }
            }
        }
    }
    entity_flags = entity_base->flags1C;
    if (entity_flags & 0x40000000) {
        entity_base->flags1C = entity_flags & 0xBFFFFFFF;
        ground_height = sample_terrain_surface_height((sprite->tile_x << 6) | 0x20,
                              (sprite->tile_y << 6) | 0x20,
                              (s16)(entity_base->ground_height - 0x20));
        if (ground_height < 0x200) {
            body->unk_90.parts.high =
                body->unk_90.parts.high +
                (entity_base->ground_height - ground_height);
            entity_base->ground_height = ground_height;
        }
    }
    motion->z.w.i = entity_base->ground_height +
                             body->unk_90.parts.high -
                             body->unk_A4.halves.high.u;
    sprite->flags |= 0x40;
}
