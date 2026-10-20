#include "common.h"
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
void start_naplass_status_action(S_80F60808_1 *action_state, void *unused, Rec_D_80082E80 *sprite, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(actor) << 0x10) == 0)) {
        action_state->unk_9A = 0xD;
        action_state->unk_8C = 0;
        action_state->unk_9B = 0;
        sprite->unk_2C.as_pm = &D_801741D4;
        select_sprite_entry(sprite, D_801741D4[(((s32) (g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7)], 0);
        actor->flags1C = (s32) (actor->flags1C | 0x200);
        set_or_clear_actor_status_slot(actor, 1, 4);
        actor->unk_46 = (u16) (actor->unk_46 & 0x7FFF);
        advance_status_timers(actor);
        actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
        g_dungeon_status.unk_0A = (u16) (((u16)g_dungeon_status.unk_0A) + 1);
    }
}
