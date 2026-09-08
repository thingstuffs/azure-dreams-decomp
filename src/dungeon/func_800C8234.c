#include "common.h"
#include "records/Rec_D_800E3D7C.h"




extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

/* Runs action 0xA when eligible, using the prior state for the flagged callback. */
s32 func_800CD994(Rec_D_800E3D7C *entity, s8 action_arg) {
    u8 updated_state;
    u8 prior_state;
    u8 initial_state;

    initial_state = entity->unk_10.at03_u8.v;
    if (initial_state != 0x2E) {
        if (((initial_state != 0x1E) || ((entity->unk_A4.at00_s32.v == 0) && (entity->unk_AA == 0))) && ((func_80042900(entity, 0xA) << 0x10) == 0)) {
            prior_state = entity->unk_10.at03_u8.v;
            if ((s16)func_800A48F0(entity, 0xA, action_arg) >= 0) {
                if (entity->unk_14.as_s32 & 0x4000) {
                    updated_state = entity->unk_10.at03_u8.v;
                    entity->unk_10.at03_u8.v = prior_state;
                    func_80099844(entity, D_800E1C25);
                    entity->unk_10.at03_u8.v = updated_state;
                }
            }
        }
    }
    return 0;
}
