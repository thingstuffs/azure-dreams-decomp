#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "engine/node/allocation.h"

typedef struct S_8017382C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { u16 s; s16 u; } unk_AC;   /* accessed as both */
    u16 unk_AE;
} S_8017382C_0;   /* arg0 in advance_actor_entry_active_exit_states */

typedef struct S_8017382C_2 {
    u8 unk_00;
} S_8017382C_2;   /* records in advance_actor_entry_active_exit_states */

typedef struct S_8017382C_3 {
    u8 pad_00[0x6];
    u16 unk_06;
} S_8017382C_3;   /* entry in advance_actor_entry_active_exit_states */

typedef struct S_8017382C_7 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x6];
    s16 unk_9E;
    s16 unk_A0;
    s16 unk_A2;
    s16 unk_A4;
    s16 unk_A6;
    s16 unk_A8;
} S_8017382C_7;   /* child in advance_actor_entry_active_exit_states */

extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern void clear_slots_of_type(ActorRecord *owner, s8 match_type);
extern void select_sprite_entry(void *, u8, s32);
extern s32 GetClut(s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s16 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void *);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80174250(void *, void *, void *, void *);

extern u8 mandara_action_resume_address[];
extern u8 mandara_object_callback[];
extern u8 mandara_frame_set_1[];

/* Advances the actor action through its entry, active, and exit animation states. */
/* Animates entry and exit palette changes for status slot 1, processes turns while active, and restores
 * the callback. */
void advance_actor_entry_active_exit_states(ActorRecord *action, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 state;
    s32 record_index;
    S_8017382C_7 *effect_state;

    state = action->action_phase.u;
    switch (state) {
    case 0:
    {
        s32 index_twice;
        s32 word_offset;
        S_8017382C_3 *facing_record;
        u8 *record;
        u8 *direction_table;
        ObjectNodeHeader *effect;
        u16 facing;

        record_index = 0;
        if (!(sprite->flags & 0xE000)) {
            return;
        }

        ((S_8017382C_0 *)action)->unk_AE = sprite->clut;
        record = *(u8 **)&sprite->source;
        while (1) {
            index_twice = record_index << 1;
            if (!(((S_8017382C_2 *)record)->unk_00 & 0x20)) {
                break;
            }
            record += 0xC;
            record_index++;
        }
        word_offset = index_twice + record_index;
        facing_record = (S_8017382C_3 *)((unsigned long)(word_offset << 2) +
                       (unsigned long)*(u8 **)&sprite->source);
        ((S_8017382C_0 *)action)->unk_AC.s =
            facing_record->unk_06 & 0xFFC0;

        direction_table = mandara_frame_set_1;
        (sprite->frameTable) = direction_table;
        select_sprite_entry(
            sprite,
            direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        effect = allocate_list_node(0x10, &scene_object_list_anchor.next);
        effect_state = (S_8017382C_7 *)((u8 *)effect + 0x20);
        if (effect != 0) {
            effect->update_callback = mandara_object_callback;
            effect_state->unk_A0 = 0;
            facing = ((S_8017382C_0 *)action)->unk_AC.s;
            effect_state->unk_A4 = 0x100;
            effect_state->unk_A6 = 1;
            effect_state->unk_A8 = 8;
            effect_state->unk_A2 = (s16)facing >> 6;
            action->action_timer.u = 8;
            effect_state->unk_96 = 0;
            effect_state->unk_9E = 0;
        }
        action->action_phase.u++;
        return;
    }

    case 1:
    {
        s32 angle_shifted;
        s32 signed_angle;
        s32 rounded_angle;
        s32 angle_remainder;
        u16 timer;

        angle_shifted = ((S_8017382C_0 *)action)->unk_AE << 16;
        signed_angle = angle_shifted >> 16;
        rounded_angle = signed_angle;
        if (rounded_angle < 0) {
            rounded_angle += 7;
        }
        angle_remainder = signed_angle - ((rounded_angle >> 3) << 3);
        sprite->clut =
            GetClut(
                ((((s32)(angle_remainder << 16) >> 18) << 6) + 0x340),
                ((angle_shifted >> 19) + 0x100)) -
            ((S_8017382C_0 *)action)->unk_AC.s;

        timer = action->action_timer.u - 1;
        action->action_timer.u = timer;
        if ((s16)timer > 0) {
            if (!(sprite->flags & 0x8000)) {
                return;
            }
        }
        sprite->clut = ((S_8017382C_0 *)action)->unk_AE - 0x40;
        action->action_phase.u++;
        return;
    }

    case 2:
    {
        s32 index_twice;
        s32 word_offset;
        u8 *facing_record;
        u8 *record;
        u8 *direction_table;
        u8 *exit_table;
        ObjectNodeHeader *effect;
        void *check_actor;
        u16 facing;

        if (((S_8017382C_0 *)action)->unk_AC.u == 0) {
            record_index = 0;
            record = *(u8 **)&sprite->source;
            while (1) {
                index_twice = record_index << 1;
                if (!(((S_8017382C_2 *)record)->unk_00 & 0x20)) {
                    break;
                }
                record += 0xC;
                record_index++;
            }
            word_offset = index_twice + record_index;
            facing_record = (u8 *)((unsigned long)(word_offset << 2) +
                           (unsigned long)*(u8 **)&sprite->source);
            ((S_8017382C_0 *)action)->unk_AC.s =
                ((S_8017382C_3 *)facing_record)->unk_06 & 0xFFC0;
        }

        if ((s16)get_entity_effect_value(actor, STATUS_SLEEP) == 0) {
            direction_table = mandara_frame_set_1;
            (sprite->frameTable) = direction_table;
            select_sprite_entry(
                sprite,
                direction_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);

            effect = allocate_list_node(0x10, &scene_object_list_anchor.next);
            effect_state = (S_8017382C_7 *)((u8 *)effect + 0x20);
            if (effect != 0) {
                effect->update_callback = mandara_object_callback;
                effect_state->unk_A0 = 0;
                facing = ((S_8017382C_0 *)action)->unk_AC.s;
                effect_state->unk_A4 = 0x100;
                effect_state->unk_A6 = 1;
                effect_state->unk_A8 = 8;
                effect_state->unk_A2 = (s16)facing >> 6;
                action->action_timer.u = 8;
                effect_state->unk_96 = 0;
                effect_state->unk_9E = 1;
            }

            ((S_8017382C_0 *)action)->unk_AE = sprite->clut + 0x40;
            g_dungeon_status.activity_counts.parts.pending_action_count++;

            action->action_phase.u++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, 0) != 0) {
                return;
            }
        }

        if (actor->mp_value.parts.whole == 0) {
            if (g_dungeon_status.flags & 0x2008) {
                return;
            }
            advance_actor_pending_action(action, context, sprite, actor);
            return;
        }

        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            return;
        }

        {
            u32 actor_flags;

            actor_flags = ((u32)actor->flags1C);
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(action, context, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(action, context, sprite, actor);
                func_80174250(action, context, sprite, actor);
                return;
            }
        }

        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((s16)has_pending_actor_or_turn_action(actor) != 0) {
            {
                ObjectNodeHeader *previous_node;
                void *previous_body;
                ActorRecord *previous_actor;

                previous_node = primary_actor_record->previous_actor_header;
                previous_body = previous_node + 1;
                previous_actor = previous_body;
                if ((s16)check_entity_relation(
                        actor, previous_actor) != 0) {
                    return;
                }
            }
        }

        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if ((s16)get_entity_effect_value(actor, STATUS_SLEEP) != 0) {
            s8 tile;

            check_actor = ((u8 *)(&reference_tile_object));
            tile = *(s8 *)&sprite->room_index;
            if ((tile != reference_tile_object.room_index) || (tile < 0)) {
                s32 distance;

                distance = (s16)get_tile_chebyshev_distance(((u8 *)(&reference_tile_object)), sprite);
                check_actor = actor;
                if (distance >= 2) {
                    goto second_call;
                }
            }
            if (!(generate_random_value(check_actor) & 7)) {
                clear_slots_of_type(actor, STATUS_SLEEP);
            }
        }

        check_actor = actor;
second_call:
        if ((s16)get_entity_effect_value(check_actor, STATUS_SLEEP) != 0) {
            return;
        }

        exit_table = mandara_frame_set_1;
        (sprite->frameTable) = exit_table;
        select_sprite_entry(
            sprite,
            exit_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);

        effect = allocate_list_node(0x10, &scene_object_list_anchor.next);
        effect_state = (S_8017382C_7 *)((u8 *)effect + 0x20);
        if (effect != 0) {
            u16 angle;
            effect->update_callback = mandara_object_callback;
            effect_state->unk_A0 = 0;
            angle = ((S_8017382C_0 *)action)->unk_AC.s;
            effect_state->unk_A4 = 0x100;
            effect_state->unk_A6 = 1;
            effect_state->unk_A8 = 8;
            effect_state->unk_A2 = (s16)angle >> 6;
            action->action_timer.u = 8;
            effect_state->unk_96 = 0;
            effect_state->unk_9E = 1;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        action->action_phase.u++;
        ((S_8017382C_0 *)action)->unk_AE = sprite->clut + 0x40;
        return;
    }

    case 3:
    {
        s32 angle_shifted;
        s32 signed_angle;
        s32 rounded_angle;
        s32 angle_remainder;
        u16 timer;

        angle_shifted = ((S_8017382C_0 *)action)->unk_AE << 16;
        signed_angle = angle_shifted >> 16;
        rounded_angle = signed_angle;
        if (rounded_angle < 0) {
            rounded_angle += 7;
        }
        angle_remainder = signed_angle - ((rounded_angle >> 3) << 3);
        sprite->clut =
            GetClut(
                ((((s32)(angle_remainder << 16) >> 18) << 6) + 0x340),
                ((angle_shifted >> 19) + 0x102)) -
            ((S_8017382C_0 *)action)->unk_AC.s;

        if (!(sprite->flags & 0x8000)) {
            timer = action->action_timer.u - 1;
            action->action_timer.u = timer;
            if ((s16)timer > 0) {
                return;
            }
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        actor->flags1C &= ~ACTOR_ASLEEP;
        action->unk_8C.address = mandara_action_resume_address;
        sprite->clut = ((S_8017382C_0 *)action)->unk_AE;
    }
    }

    return;
}
