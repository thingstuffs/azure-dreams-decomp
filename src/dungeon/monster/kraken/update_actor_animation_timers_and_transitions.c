#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/kraken.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_trail_views.h"

typedef struct S_8017352C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
    u8 pad_9C[0x8];
    u8 * unk_A4;
    u16 unk_A8;
} S_8017352C_0;   /* arg0 in update_actor_animation_timers_and_transitions */

   /* arg2 in update_actor_animation_timers_and_transitions */

typedef struct S_8017352C_2 {
    u8 pad_00[0x1C];
    union { s32 s; u32 u; } unk_1C;   /* accessed as both */
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017352C_2;   /* arg3 in update_actor_animation_timers_and_transitions */

   /* counter_base in update_actor_animation_timers_and_transitions */

typedef struct S_8017352C_5 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_8017352C_5;   /* part20 in update_actor_animation_timers_and_transitions */

   /* part28 in update_actor_animation_timers_and_transitions */


extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 rand(void);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 has_pending_actor_or_turn_action(void *);
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, s32);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void func_80173D10(void *, void *, void *, void *);

extern u8 D_801711A4[];
extern u8 D_80174184[];
extern u8 kraken_frame_set_2[];

/* Updates the actor's animation state, timers, and action transitions. */
void update_actor_animation_timers_and_transitions(void *entity, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    u8 *body_part;
    SpriteFrameState *part_anim;
    DungeonGlobalStatus *global_base;
    u8 *body;
    DungeonGlobalStatus *state_zero_counter_base;
    DungeonGlobalStatus *animate_counter_base;
    u8 *state_two_counter_base;
    s32 actor_flags;
    s32 state;
    u16 timer;
    u16 count;

    body = ((S_8017352C_0 *)entity)->unk_A4;
    state = ((S_8017352C_0 *)entity)->unk_9B;
    body_part = body + 0x20;
    part_anim = body + 0x28;
    switch (state) {
    case 0:
        ((S_8017352C_0 *)entity)->unk_90 += 0x80000;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        (sprite->frameTable) = kraken_frame_set_2;
        select_sprite_entry(sprite,
            kraken_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        state_zero_counter_base = &g_dungeon_status;
        ((S_8017352C_0 *)entity)->unk_96 = 0;
        count = ((u16)state_zero_counter_base->activity_counts.parts.pending_action_count) - 1;
        state_zero_counter_base->activity_counts.parts.pending_action_count = count;
        ((S_8017352C_0 *)entity)->unk_9B++;
        return;
    case 1:
        if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (((S_8017352C_2 *)actor)->unk_64 != 0) {
                if (begin_ready_actor_directional_action(entity, motion, sprite, 0) != 0) {
                    return;
                }
            }
            if (((S_8017352C_2 *)actor)->unk_25 == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(entity, motion, sprite, actor);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                return;
            }
            actor_flags = ((S_8017352C_2 *)actor)->unk_1C.s;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(entity, motion, sprite, actor);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(entity, motion, sprite, actor);
                ((S_8017352C_0 *)entity)->unk_A8 = 0;
                func_80173D10(entity, motion, sprite, actor);
                return;
            }

            timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
            ((S_8017352C_0 *)entity)->unk_96 = timer;
            if ((timer << 16) <= 0) {
                ((S_8017352C_5 *)body_part)->unk_04 &= 0x7FFF;
                select_sprite_entry(part_anim, 0x27, 0);
                ((S_8017352C_0 *)entity)->unk_96 = (rand() & 0xF) + 0x20;
            }
            if (part_anim->flags & 0x6000) {
                ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            }
            if (((S_8017352C_2 *)actor)->unk_6D == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(actor,
                        (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor);
            on_actor_status_updated(actor);
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&sprite->unk_26;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, sprite) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor, STATUS_SLEEP) << 16) != 0) {
                return;
            }
            (sprite->frameTable) = D_80174184;
            select_sprite_entry(sprite,
                D_80174184[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_8017352C_2 *)actor)->unk_1C.u |= 0x40000;
            ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            if (!(sprite->flags & 0x8000)) {
                animate_counter_base = (u8 *)3;
                ((S_8017352C_0 *)entity)->unk_96 = (s32)animate_counter_base;
                ((S_8017352C_0 *)entity)->unk_98 &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.turn_scale;
                count = *(u16 *)&animate_counter_base->activity_counts.parts.pending_action_count + 1;
                animate_counter_base->activity_counts.parts.pending_action_count = count;
                ((S_8017352C_0 *)entity)->unk_9B++;
                return;
            }
            break;
        } else {
            (sprite->frameTable) = D_80174184;
            select_sprite_entry(sprite,
                D_80174184[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8017352C_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_8017352C_2 *)actor)->unk_1C.u |= 0x40000;
            ((S_8017352C_5 *)body_part)->unk_04 |= 0x8000;
            if (!(sprite->flags & 0x8000)) {
                animate_counter_base = (u8 *)3;
                ((S_8017352C_0 *)entity)->unk_96 = (s32)animate_counter_base;
                ((S_8017352C_0 *)entity)->unk_98 &= 0xBFFF;
                animate_counter_base = (u8 *)&g_dungeon_status.turn_scale;
                count = *(u16 *)&animate_counter_base->activity_counts.parts.pending_action_count + 1;
                animate_counter_base->activity_counts.parts.pending_action_count = count;
                ((S_8017352C_0 *)entity)->unk_9B++;
                return;
            }
            break;
        }
    case 2:
        timer = ((S_8017352C_0 *)entity)->unk_96 - 1;
        ((S_8017352C_0 *)entity)->unk_96 = timer;
        if ((timer << 16) <= 0) {
            ((S_8017352C_0 *)entity)->unk_98 |= 0x4000;
            motion->velocity_z = 0xFFF80000;
        }
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        state_two_counter_base = (u8 *)&g_dungeon_status.turn_scale;
        motion->velocity_z = 0;
        ((S_8017352C_0 *)entity)->unk_A8 = 0;
        ((TrailHeightView *)state_two_counter_base)->unk_0A--;

        break;
    default:
        return;
    }
    ((S_8017352C_2 *)actor)->unk_1C.u &= -0x201;
    ((S_8017352C_0 *)entity)->unk_8C = D_801711A4;
}
