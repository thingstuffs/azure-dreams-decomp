#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct Ent Ent;
Ent *prepare_directional_attack(); /* extern */
s32 try_claim_dungeon_action_slot();                          /* extern */
s32 apply_camera_offset_and_select_target(); /* extern */


typedef struct S_80172AAC_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172AAC_1;   /* arg0 in apply_conditional_actor_effect */

/* Clears an actor flag, applies a conditional effect, and updates its action state. */
void apply_conditional_actor_effect(S_80172AAC_1 *action_state, void *effect_context, void *action_context, EntityRec *actor) {
    actor->unk_71 = (u8) (actor->unk_71 & 0x7F);
    if (!(g_dungeon_status.flags & 0x2000) && ((try_claim_dungeon_action_slot(actor) << 0x10) == 0)) {
        apply_camera_offset_and_select_target((u8 *)actor - 0x20, effect_context, 8, 0x300);
        if ((try_claim_dungeon_action_slot(actor) << 0x10) == 0) {
            action_state->unk_8C = 0;
            action_state->unk_9A = 0x11;
            action_state->unk_9B = 0;
            actor->unk_6D = (u8) (((u8)actor->unk_6D) - 1);
            prepare_directional_attack(actor, action_context, actor->facing, 1, 0);
            actor->unk_84 = 0x7C;
            actor->unk_85 = 4;
        }
    }
}
