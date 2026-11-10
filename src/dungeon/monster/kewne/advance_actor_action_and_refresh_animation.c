#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/system/random.h"
#include "dungeon/monster/kewne.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "engine/entity.h"


extern s32 get_tile_chebyshev_distance(void *, void *);
#include "dungeon/player/object/action_state.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/monster/kewne_frames.h"

#include "dungeon/actor/state.h"

extern void update_actor_state_after_map_check(void *, ObjectPosition *, void *, ActorRecord *);

extern u8 kewne_action_resume_address[];

/* Advances the actor action state, updating its directional animation and callback. */
void advance_actor_action_and_refresh_animation(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *render_record, ActorRecord *actor_state) {
    s32 actor_flags;
    u16 value;
    u16 value_offset;
    DungeonGlobalStatus *global_base;
    s32 state;

    state = actor->action_phase;
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
            actor->action_phase++;
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
                value = actor->unk_90.parts.high;
                value_offset = actor->unk_A0.parts.high;
                actor->unk_A0.parts.high = 0;
                actor->unk_9E = 0;
                actor->unk_90.parts.high = value - value_offset;
                update_actor_state_after_map_check(actor, context, render_record, actor_state);
                return;
            }
            if (actor_state->pending_turn_updates == 0) {
                return;
            }
            if ((has_pending_actor_or_turn_action(actor_state) << 16) != 0) {
                ActorRecord *owner = primary_actor_record;

                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = owner->previous_actor_header;
                    previous_body = NODE_BODY(previous_node);
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor_state,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            update_actor_status_and_mp(actor_state);
            on_actor_status_updated(actor_state);
            if ((get_entity_effect_value(actor_state, STATUS_SLEEP) << 16) != 0) {
                TileObject *origin = &reference_tile_object;
                s8 tile = ((s8)(render_record->room_index));

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
        actor_state->flags1C = (u32)((u32)(actor_state->flags1C) | (0x40000));
        if (render_record->flags & 0x8000) {
            actor->unk_8C.address = kewne_action_resume_address;
            return;
        }
        actor->action_phase++;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
        return;

    case 2:
        if (!(render_record->flags & 0xE000)) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;

        actor->unk_8C.address = kewne_action_resume_address;
        return;
    }
}
