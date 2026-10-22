#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801590EC_0 {
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
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_801590EC_0;   /* arg0 in update_actor_behavior_from_position */


typedef struct S_801590EC_2 {
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
} S_801590EC_2;   /* arg2 in update_actor_behavior_from_position */


extern s32 get_entity_effect_value(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015969C(void *, void *, void *, void *);
extern void func_80159854(void *, void *, void *, void *);
extern s32 func_80159F9C(void *, void *, void *, void *);
extern void func_8015A234(void *, void *, void *, void *);
extern void func_8015A358(void *, void *, void *, void *);
extern s32 func_8015A66C(void *, void *, void *, s32);
extern void func_8015C574(void *, void *, void *, void *);

extern u8 D_8015DE40[];
extern u8 D_8015DE48[];
extern u8 D_8015DE98[];
extern u8 D_8015DEA0[];
extern u8 D_8015DEB0[];
extern u8 D_8015DEB8[];

/* Update actor animation, behavior, and facing from its status and player position. */
void update_actor_behavior_from_position(void *actor, void *context, void *sprite, ActorRecord *entity)
{
    s32 facing_aux;
    s8 room_id;
    u16 behavior_flags;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_801590EC_0 *)actor)->unk_9A = 0xE;
        func_8015969C(actor, context, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (((S_801590EC_2 *)sprite)->unk_2C == D_8015DEA0) {
            return;
        }
        anim_table = D_8015DEB0;
        (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
        select_sprite_entry(sprite,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_801590EC_2 *)sprite)->unk_2C == D_8015DEA0) {
            ((S_801590EC_0 *)actor)->unk_9A = 0xD;
            ((S_801590EC_0 *)actor)->unk_9B = 1;
            ((S_801590EC_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_8015DEB0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anim;
            u8 *anim_table;

            if (((S_801590EC_0 *)actor)->unk_9A != 0xE) {
                ((S_801590EC_0 *)actor)->unk_9A = 0xE;
                ((S_801590EC_0 *)actor)->unk_B2 = 0;
            }

            current_anim = ((S_801590EC_2 *)sprite)->unk_2C;
            if (current_anim == D_8015DEB8) {
                if (((S_801590EC_2 *)sprite)->unk_14 & 0xE000) {
                    u8 *reset_anim_table = D_8015DE40;

                    (*(void * *)((u8 *)sprite + 0x2C)) = reset_anim_table;
                    select_sprite_entry(sprite,
                        reset_anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_801590EC_2 *)sprite)->unk_05 = 1;
                    ((S_801590EC_0 *)actor)->unk_A2.s = 0;
                    ((S_801590EC_0 *)actor)->unk_9E = 0;
                }
            } else {
                anim_table = D_8015DE40;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_801590EC_2 *)sprite)->unk_05 = 1;
                    ((S_801590EC_0 *)actor)->unk_A2.s = 0;
                    ((S_801590EC_0 *)actor)->unk_9E = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        ((S_801590EC_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8015DE48) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            s16 position_delta;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            position_delta = ((S_801590EC_0 *)actor)->unk_92.u - ((S_801590EC_0 *)actor)->unk_A2.u;
            ((S_801590EC_0 *)actor)->unk_A2.s = 0;
            ((S_801590EC_0 *)actor)->unk_9E = 0;
            ((S_801590EC_0 *)actor)->unk_92.s = position_delta;
            func_8015C574(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(((S_801590EC_2 *)sprite)->unk_24.at00.v, ((S_801590EC_2 *)sprite)->unk_24.at01.v);
    ((S_801590EC_2 *)sprite)->unk_26 = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (((S_801590EC_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_80159854(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8015A66C(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            behavior_flags = entity->action_flags | 0x4000;
            entity->action_flags = behavior_flags;
            if (!(behavior_flags & 0x8000)) {
                func_80159854(actor, context, sprite, entity);
                return;
            }
        }

        switch ((entity->action_flags & ACTOR_ACTION_CODE_MASK) - 1) {
        case 7:
        case 8:
sw_case89:
            if ((func_80159F9C(actor, context, sprite, entity) << 16) != 0) {
                return;
            }
            func_8015A234(actor, context, sprite, entity);
            return;

        case 4:
        case 5:
        case 6:
sw_case567:
            {
                ActorRecord *player;
                s16 facing_angle;

                facing_angle = get_rounded_facing_and_rounding_flag(
                    ((S_801590EC_2 *)sprite)->unk_24.at00.v, ((S_801590EC_2 *)sprite)->unk_24.at01.v,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &facing_aux);
                player = primary_actor_record;
                entity->facing = facing_angle;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_8015DE98, update_actor_behavior_from_position);
                    return;
                }
            }
                                    /* fallthrough */

        case 11:
            update_actor_status_and_mp(entity);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_8015DE98, update_actor_behavior_from_position);
            return;

        default:
            func_80159854(actor, context, sprite, entity);
            return;
        }
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((test_neighbor_position_relation(
                        ((S_801590EC_2 *)sprite)->unk_24.at00.v, ((S_801590EC_2 *)sprite)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        ((S_801590EC_2 *)sprite)->unk_24.at00.v, ((S_801590EC_2 *)sprite)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &facing_aux);
                    return;
                }
            }
        }
    } else if ((get_entity_effect_value(entity, 4) << 16) == 0) {
        if (primary_actor_record->unk_9A == 0x17) {
            func_8015A358(actor, context, sprite, entity);
        }
    }
}
