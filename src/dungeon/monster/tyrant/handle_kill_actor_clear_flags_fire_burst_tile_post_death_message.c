#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/monster/tyrant/handle_kill_actor_clear_flags_fire_burst_tile_post_death_message.h"
#include "shared/sprite_frame_state.h"

/* Kill the actor: clear its flags, fire the burst at its tile and post its death message. */
void handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(void *work_in, ObjectPosition *part_a, SpriteFrameState *part_b_in, ActorRecord *actor) {
    s32 burst;
    void *handle;
    void *msg;
    void *msg_actor;
    void *msg_handle;
    u8 flags71;
    u8 call_a0;
    u8 call_a1;
    s32 call_flags;
    T_80173AD4_S_80173AD4_2 *work;
    SpriteFrameState *part_b;

    flags71 = actor->movement_queue_state;
    work = work_in;
    actor->movement_queue_state = flags71 & 0x7F;
    part_b = part_b_in;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        work->unk_8C = 0;
        work->unk_9A = 0x17;
        work->unk_9B = 0;
        work->unk_96 = 0;
        if (!(work->unk_98 & 0x8000)) {
            work->unk_A6 = (u16) part_b->clut;
            work->unk_AA = (s16) (((T_80173AD4_S_80173AD4_0 *)actor)->unk_14 & 7);
        }
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        actor->pending_turn_updates = (u8) (actor->pending_turn_updates - 1);
        call_flags = actor->flags1C & 0x2000;
        call_a0 = part_b->tile_x;
        call_a1 = part_b->tile_y;
        burst = 0x3000;
        if (call_flags) {
            burst = 0x300;
        }
        update_map_cell_flags_with_item_limit(call_a0, call_a1, burst);
        actor->flags1C = (s32) (actor->flags1C & ~0x2000);
        cycle_map_cell_flags(part_b->tile_x, part_b->tile_y, 0x3000);
        (part_b->frameTable) = tyrant_frame_set_1;
        select_sprite_entry(part_b, tyrant_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0);
        msg = get_unused_text_buffer();
        msg_actor = actor;
        msg_handle = msg;
        msg = append_entity_display_text(msg_actor, msg_handle);
        handle = msg_handle;
        clear_byte_and_advance(expand_text_control_codes(&D_80170854, msg));
        display_text_with_fullwidth_adjustment(handle);
    }
}
