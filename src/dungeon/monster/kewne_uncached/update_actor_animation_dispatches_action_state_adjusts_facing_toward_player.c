#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_8015FFA4_0 {
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
} S_8015FFA4_0;   /* arg0 in update_actor_animation_dispatches_action_state_adjusts_facing_toward_player */

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);
extern void func_80160510(void *, void *, void *, void *);
extern void func_801606C8(void *, void *, void *, void *);
extern s32 func_80160E10(void *, void *, void *, void *);
extern void func_801610A8(void *, void *, void *, void *);
extern s32 func_801611CC(void *, void *, void *, void *);
extern void func_80163078(void *, void *, void *, void *);

extern u8 D_8015FFA4[];
extern u8 kewne_uncached_frame_set_3[];
extern u8 D_80163C38[];
extern u8 D_80163C88[];
extern u8 D_80163C90[];
extern u8 D_80163CA0[];
extern u8 D_80163CA8[];

/* Updates actor animation, dispatches its action state, and adjusts facing toward the player. */
void update_actor_animation_dispatches_action_state_adjusts_facing_toward_player(void *actor, ObjectPosition *actor_aux, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 direction_aux;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_8015FFA4_0 *)actor)->unk_9A = 0xE;
        func_80160510(actor, actor_aux, sprite, entity);
        return;
    }
    if (entity->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(actor, actor_aux, sprite, entity);
        if (sprite->frameTable == D_80163C90) {
            return;
        }
        anim_table = D_80163CA0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_80163C90) {
            ((S_8015FFA4_0 *)actor)->unk_9A = 0xD;
            ((S_8015FFA4_0 *)actor)->unk_9B = 1;
            ((S_8015FFA4_0 *)actor)->unk_8C = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, actor_aux, sprite, D_80163CA0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, actor_aux, sprite, entity);
            return;
        }

        {
            u8 current_state = ((S_8015FFA4_0 *)actor)->unk_9A;
            u32 next_state = 0xE;
            void *current_anim;

            if (current_state != next_state) {
                ((S_8015FFA4_0 *)actor)->unk_9A = next_state;
                ((S_8015FFA4_0 *)actor)->unk_B6 = 0;
            }
            current_anim = sprite->frameTable;
            if (current_anim != D_80163CA8 || (sprite->flags & 0xE000)) {
                if (current_anim == D_80163CA8) {
                    (sprite->frameTable) = kewne_uncached_frame_set_3;
                    select_sprite_entry(sprite,
                        kewne_uncached_frame_set_3[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                } else {
                    void *idle_anim = kewne_uncached_frame_set_3;
                    if (current_anim == idle_anim) {
                        goto table_done;
                    }
                    (sprite->frameTable) = idle_anim;
                    select_sprite_entry(sprite,
                        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                        0);
                }
                sprite->frame_ticks = 1;
                ((S_8015FFA4_0 *)actor)->unk_A2.s = 0;
                ((S_8015FFA4_0 *)actor)->unk_9E = 0;
            }
        }
table_done:

        (*(u32 *)&entity->flags1C) |= 0x40000;
        ((S_8015FFA4_0 *)actor)->unk_98 &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, actor_aux, sprite, D_80163C38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 base_height;

            begin_actor_move_to_target_facing(actor, actor_aux, sprite, entity);
            base_height = ((S_8015FFA4_0 *)actor)->unk_92.u - ((S_8015FFA4_0 *)actor)->unk_A2.u;
            ((S_8015FFA4_0 *)actor)->unk_A2.s = 0;
            ((S_8015FFA4_0 *)actor)->unk_9E = 0;
            ((S_8015FFA4_0 *)actor)->unk_92.s = base_height;
            func_80163078(actor, actor_aux, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, actor_aux, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_801606C8(actor, actor_aux, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801611CC(actor, actor_aux, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->action_flags | 0x4000;
            entity->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                func_801606C8(actor, actor_aux, sprite, entity);
                return;
            }
        }

        action_state = entity->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_state) {
        case 8:
        case 9:
            if ((func_80160E10(actor, actor_aux, sprite, entity) << 16) != 0) {
                return;
            }
            func_801610A8(actor, actor_aux, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            ActorRecord *player;
            s16 facing;

            facing = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
            player = primary_actor_record;
            entity->facing = facing;
            if (player->action_id.u == 0x11) {
                begin_actor_spell_action(actor, actor_aux, sprite, D_80163C88, D_8015FFA4);
                return;
            }
        }

        case 12:
            update_actor_status_and_mp(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, actor_aux, sprite, D_80163C88, D_8015FFA4);
            return;

        case 11:
        default:
            func_801606C8(actor, actor_aux, sprite, entity);
            return;
        }
    }

    if (!(((u32)entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }
}
