#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "shared/entity.h"


extern s32 func_80042900();
extern void adjust_source_value_and_finalize();
extern s16 set_or_clear_actor_status_slot();
extern u8 D_800E1C25[];

/* Runs action 0xA when eligible, using the prior state for the flagged callback. */
s32 run_action_ten_if_eligible(EntityRec *entity, s8 action_arg) {
    u8 updated_state;
    u8 prior_state;
    u8 initial_state;

    initial_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
    if (initial_state != 0x2E) {
        if (((initial_state != 0x1E) || ((entity->unk_A4 == 0) && (entity->unk_AA == 0)))
            && ((func_80042900(entity, 0xA) << 0x10) == 0)) {
            prior_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
            if ((s16)set_or_clear_actor_status_slot(entity, 0xA, action_arg) >= 0) {
                if (entity->flags14 & 0x4000) {
                    updated_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
                    (*(u8 *)((u8 *)&entity->unk_10 + 3)) = prior_state;
                    adjust_source_value_and_finalize(entity, D_800E1C25);
                    (*(u8 *)((u8 *)&entity->unk_10 + 3)) = updated_state;
                }
            }
        }
    }
    return 0;
}
