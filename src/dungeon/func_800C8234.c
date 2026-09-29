#include "common.h"
#include "shared/entity.h"


extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

/* Runs action 0xA when eligible, using the prior state for the flagged callback. */
s32 func_800CD994(EntityRec *entity, s8 action_arg) {
    u8 updated_state;
    u8 prior_state;
    u8 initial_state;

    initial_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
    if (initial_state != 0x2E) {
        if (((initial_state != 0x1E) || ((entity->unk_A4 == 0) && (entity->unk_AA == 0)))
            && ((func_80042900(entity, 0xA) << 0x10) == 0)) {
            prior_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
            if ((s16)func_800A48F0(entity, 0xA, action_arg) >= 0) {
                if (entity->flags14 & 0x4000) {
                    updated_state = (*(u8 *)((u8 *)&entity->unk_10 + 3));
                    (*(u8 *)((u8 *)&entity->unk_10 + 3)) = prior_state;
                    func_80099844(entity, D_800E1C25);
                    (*(u8 *)((u8 *)&entity->unk_10 + 3)) = updated_state;
                }
            }
        }
    }
    return 0;
}
