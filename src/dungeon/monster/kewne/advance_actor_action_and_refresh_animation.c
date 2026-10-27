#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173E50_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80173E50_0;   /* arg0 in advance_actor_action_and_refresh_animation */

extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
extern s32 generate_random_value(void);
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_actor_state_after_map_check(void *, ObjectPosition *, void *, ActorRecord *);
extern void * create_randomized_motion_object(void *, void *);

extern u8 kewne_action_resume_address[];
extern u8 kewne_frame_set_1[];
extern u8 kewne_frame_set_2[];

/* Advances the actor action state, updating its directional animation and callback. */
void advance_actor_action_and_refresh_animation(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *render_record, ActorRecord *actor_state) {
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = actor->action_phase.u;
    switch (state) {
    case 0:
        if (!(render_record->flags & 0xE000)) {
            return;
        }
        render_record->frameTable = kewne_frame_set_1;
        select_sprite_entry(render_record,
            kewne_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
            0);
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_809A2650). */
        do {
            actor->action_phase.u++;
        } while (0);
        return;

    case 1:
        if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
            global_base = &g_dungeon_status;
            if (global_base->flags & 0x1000) {
                return;
            }
            if (actor_state->hp_delta != 0) {
                if (begin_ready_actor_directional_action(actor, context, render_record, 0) != 0) {
                    return;
                }
            }
            if (actor_state->mp_value.parts.whole == 0) {
                if (global_base->flags & 0x2008) {
                    return;
                }
                advance_actor_pending_action(actor, context, render_record, actor_state);
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                return;
            }
            actor_flags = actor_state->flags1C;
            if (actor_flags & 0x100) {
                begin_pushed_actor_move(actor, context, render_record, actor_state);
                return;
            }
            if (actor_flags & 0x80000) {
                begin_actor_move_to_target_facing(actor, context, render_record, actor_state);
                value = ((S_80173E50_0 *)actor)->unk_92;
                value_offset = ((S_80173E50_0 *)actor)->unk_A2;
                ((S_80173E50_0 *)actor)->unk_A2 = 0;
                ((S_80173E50_0 *)actor)->unk_9E = 0;
                ((S_80173E50_0 *)actor)->unk_92 = value - value_offset;
                update_actor_state_after_map_check(actor, context, render_record, actor_state);
                return;
            }
            if (actor_state->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                if ((check_entity_relation(actor_state,
                        (u8 *)owner->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            update_actor_status_and_mp(actor_state);
            on_actor_status_updated(actor_state);
            if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = *(s8 *)&render_record->room_index;

                if (((tile == origin->room_index) && (tile >= 0)) ||
                    ((s16)get_tile_chebyshev_distance(origin, render_record) < 2)) {
                    if (!(generate_random_value() & 7)) {
                        clear_slots_of_type(actor_state, STATUS_SLEEP);
                    }
                }
            }
            if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
                return;
            }
        }
        render_record->frameTable = kewne_frame_set_2;
        select_sprite_entry(render_record,
            kewne_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + actor_state->facing + 0x100) >> 9) & 7],
            0);
        (*(u32 *)&actor_state->flags1C) |= 0x40000;
        if (render_record->flags & 0x8000) {
            ((S_80173E50_0 *)actor)->unk_8C = kewne_action_resume_address;
            return;
        }
        actor->action_phase.u++;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        return;

    case 2:
        if (!(render_record->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        ((S_80173E50_0 *)actor)->unk_8C = kewne_action_resume_address;
        return;
    }
}
