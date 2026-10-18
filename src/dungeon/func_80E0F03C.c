#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_801764A0[];
s16 try_claim_dungeon_action_slot();                          /* extern */
s32 advance_status_timers();                      /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */


typedef struct S_8017283C_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_8017283C_1;   /* arg0 in clear_actor_action_flag_and_animate */


/* Clear the actor flag and, when allowed, start a directional animation and update its action state. */
void clear_actor_action_flag_and_animate(S_8017283C_1 *action_state, M2C_UNK action_context, Rec_D_80082E80 *animation, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, action_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_9A = 0x18;
            action_state->unk_8C = 0;
            action_state->unk_9B = 0;
            animation->unk_2C.as_pu8 = D_801764A0;
            func_80047784(animation, D_801764A0[((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7], 0);
            advance_status_timers(actor);
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            action_state->unk_98 = (u16) (action_state->unk_98 | 8);
        }
    }
}
