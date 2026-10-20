#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_801764A0[];
s16 try_claim_dungeon_action_slot();                          /* extern */
s32 advance_status_timers();                      /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */


typedef struct S_8017294C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8017294C_1;   /* arg0 in attempt_actor_directional_action */


/* Attempt an actor action and initialize its state and directional animation on success. */
void attempt_actor_directional_action(S_8017294C_1 *action_state, s32 action_ctx, Rec_D_80082E80 *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_ctx, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x19;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            sprite->unk_2C.as_pu8 = D_801764A0;
            select_sprite_entry(sprite, D_801764A0[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            advance_status_timers(actor);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
        }
    }
}
