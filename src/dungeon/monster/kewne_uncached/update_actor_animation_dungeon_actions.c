#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80153FA4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80153FA4_0;   /* arg0 in update_actor_animation_dungeon_actions */


typedef struct S_80153FA4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80153FA4_2;   /* arg2 in update_actor_animation_dungeon_actions */


extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_80154510(void *, void *, void *, void *);
extern void func_801546C8(void *, void *, void *, void *);
extern s32 func_80154E10(void *, void *, void *, void *);
extern void func_801550A8(void *, void *, void *, void *);
extern s32 func_801551CC(void *, void *, void *, void *);
extern void func_80157078(void *, void *, void *, void *);

extern u8 D_80153FA4[];
extern u8 D_80157C30[];
extern u8 D_80157C38[];
extern u8 D_80157C88[];
extern u8 D_80157C90[];
extern u8 D_80157CA0[];
extern u8 D_80157CA8[];

/* Updates the actor animation and dispatches dungeon actions based on its state. */
void update_actor_animation_dungeon_actions(void *actor, void *context, void *sprite, ActorRecord *entity)
{
    s32 distance;
    s8 room_id;
    u16 action;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_80153FA4_0 *)actor)->unk_9A = 0xE;
        func_80154510(actor, context, sprite, entity);
        return;
    }
    if (entity->mp == 0) {
        void *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (((S_80153FA4_2 *)sprite)->unk_2C == D_80157C90) {
            return;
        }
        anim_table = D_80157CA0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_80153FA4_2 *)sprite)->unk_2C == D_80157C90) {
            ((S_80153FA4_0 *)actor)->unk_9A = 0xD;
            ((S_80153FA4_0 *)actor)->unk_9B = 1;
            ((S_80153FA4_0 *)actor)->unk_8C = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80157CA0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            u8 current_state = ((S_80153FA4_0 *)actor)->unk_9A;
            u32 idle_state = 0xE;
            void *current_anim;

            if (current_state != idle_state) {
                ((S_80153FA4_0 *)actor)->unk_9A = idle_state;
                ((S_80153FA4_0 *)actor)->unk_B6 = 0;
            }
            current_anim = ((S_80153FA4_2 *)sprite)->unk_2C;
            if (current_anim == D_80157CA8) {
                if (((S_80153FA4_2 *)sprite)->unk_14 & 0xE000) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = D_80157C30;
                    select_sprite_entry(sprite,
                        D_80157C30[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_80153FA4_2 *)sprite)->unk_05 = 1;
                    ((S_80153FA4_0 *)actor)->unk_A2.s = 0;
                    ((S_80153FA4_0 *)actor)->unk_9E = 0;
                }
            } else {
                void *idle_anim = D_80157C30;
                if (current_anim != idle_anim) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = idle_anim;
                    select_sprite_entry(sprite,
                        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                        0);
                    ((S_80153FA4_2 *)sprite)->unk_05 = 1;
                    ((S_80153FA4_0 *)actor)->unk_A2.s = 0;
                    ((S_80153FA4_0 *)actor)->unk_9E = 0;
                }
            }
        }

        (*(u32 *)&entity->flags1C) |= 0x40000;
        ((S_80153FA4_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80157C38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            adjusted_offset = ((S_80153FA4_0 *)actor)->unk_92.u - ((S_80153FA4_0 *)actor)->unk_A2.u;
            ((S_80153FA4_0 *)actor)->unk_A2.s = 0;
            ((S_80153FA4_0 *)actor)->unk_9E = 0;
            ((S_80153FA4_0 *)actor)->unk_92.s = adjusted_offset;
            func_80157078(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(((S_80153FA4_2 *)sprite)->unk_24.at00.v, ((S_80153FA4_2 *)sprite)->unk_24.at01.v);
    ((S_80153FA4_2 *)sprite)->unk_26 = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (((S_80153FA4_2 *)sprite)->unk_24.at00u.v != *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            if (!(entity->action_flags & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(entity,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801551CC(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action = entity->action_flags | 0x4000;
                entity->action_flags = action;
            }

            if (entity->action_flags & 0x8000) {
                action = entity->action_flags & 0x3FFF;
                switch (action) {
                case 8:
                case 9:
                    if ((func_80154E10(actor, context, sprite, entity) << 16) != 0) {
                        return;
                    }
                    func_801550A8(actor, context, sprite, entity);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    ActorRecord *player;
                    s16 facing;

                    facing = get_rounded_facing_and_rounding_flag(
                        ((S_80153FA4_2 *)sprite)->unk_24.at00.v, ((S_80153FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &distance);
                    player = D_800814A8;
                    entity->facing = facing;
                    if (player->unk_9A == 0x11) {
                        begin_actor_spell_action(actor, context, sprite, D_80157C88, D_80153FA4);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_food(entity);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(actor, context, sprite, D_80157C88, D_80153FA4);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }

        func_801546C8(actor, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((S_80153FA4_2 *)sprite)->unk_24.at00.v, ((S_80153FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        ((S_80153FA4_2 *)sprite)->unk_24.at00.v, ((S_80153FA4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }
}
