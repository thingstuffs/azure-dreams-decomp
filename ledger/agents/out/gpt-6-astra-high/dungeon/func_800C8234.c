#include "common.h"

typedef struct S_800CD994_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x8C];
    s32 unk_A4;
    u8 pad_A8[0x2];
    s16 unk_AA;
} S_800CD994_0;   /* arg0 in func_800CD994 */



extern s32 func_80042900(void *, s8);
extern s32 func_80099844(void *, void *);
extern s32 func_800A48F0(void *, s8, s8);
extern u8 D_800E1C25[];

/* Runs action 0xA when eligible, using the prior state for the flagged callback. */
s32 func_800CD994(S_800CD994_0 *entity, s8 action_arg) {
    u8 updated_state;
    u8 prior_state;
    u8 initial_state;

    initial_state = entity->unk_13;
    if (initial_state != 0x2E) {
        if (((initial_state != 0x1E) || ((entity->unk_A4 == 0) && (entity->unk_AA == 0))) && ((func_80042900(entity, 0xA) << 0x10) == 0)) {
            prior_state = entity->unk_13;
            if ((s16)func_800A48F0(entity, 0xA, action_arg) >= 0) {
                if (entity->unk_14 & 0x4000) {
                    updated_state = entity->unk_13;
                    entity->unk_13 = prior_state;
                    func_80099844(entity, D_800E1C25);
                    entity->unk_13 = updated_state;
                }
            }
        }
    }
    return 0;
}
