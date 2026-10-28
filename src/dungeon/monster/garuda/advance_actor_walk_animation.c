#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80047784 S_80047784;

typedef struct S_801722E0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xC];
    void * unk_A8;
} S_801722E0_2;

extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes();
extern void * clear_byte_and_advance(s8 *byte_ptr);
extern u8 *append_entity_display_text();
#include "dungeon/player/object/action_state.h"
extern s32 display_text_with_fullwidth_adjustment();

extern u8 D_80170838[16];
extern u8 garuda_walk_text[16];
extern u8 garuda_walk_direction_frames[9];

#line 1 "a"
/* Step the actor's walk animation: clear its 0x71 busy bit and, when the global 0x2000 mode is off and the ready query says 0, arm state 0x17, point the part at the direction table and advance the shared counters. */
void advance_actor_walk_animation(ActorRecord *owner, ObjectPosition *unused, SpriteFrameState *part, ActorRecord *actor) {
    s32 original_value;
    s32 current_value;
    s32 adjusted_value;

    actor->movement_queue_state = (u8)(actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) &&
        ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        u8 *table = garuda_walk_direction_frames;

        owner->action_id.s = 0x17;
        ((S_801722E0_2 *)owner)->unk_8C = 0;
        owner->action_phase.s = 0;
        (part->frameTable) = table;
        select_sprite_entry(
            part,
            table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        actor->pending_turn_updates = (u8)(((u8)actor->pending_turn_updates) - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        adjusted_value = append_entity_display_text(actor, current_value = get_unused_text_buffer());
        original_value = current_value;
        current_value = adjusted_value;
        clear_byte_and_advance(expand_text_control_codes(
            garuda_walk_text,
            append_entity_display_text(((S_801722E0_2 *)owner)->unk_A8,
                expand_text_control_codes(D_80170838, current_value))));
        display_text_with_fullwidth_adjustment(original_value);
    }
}
