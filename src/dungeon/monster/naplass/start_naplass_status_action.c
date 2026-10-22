#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 has_pending_dungeon_activity();                          /* extern */
s16 set_or_clear_actor_status_slot();    /* extern */
s32 advance_status_timers();                      /* extern */
extern u8 D_801741D4[8];

typedef struct S_80F60808_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80F60808_1;   /* arg0 in start_naplass_status_action */

/* Start the actor's directional animation and update its action state when allowed. */
void start_naplass_status_action(S_80F60808_1 *action_state, void *unused, SpriteFrameState *sprite, ActorRecord *actor) {
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        action_state->unk_9A = 0xD;
        action_state->unk_8C = 0;
        action_state->unk_9B = 0;
        sprite->frameTable = &D_801741D4;
        select_sprite_entry(sprite, D_801741D4[(((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7)], 0);
        actor->flags1C = (s32) (actor->flags1C | 0x200);
        set_or_clear_actor_status_slot(actor, 1, 4);
        actor->action_flags = (u16) (actor->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        advance_status_timers(actor);
        actor->pending_turn_updates = (u8) (((u8)actor->pending_turn_updates) - 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
    }
}
