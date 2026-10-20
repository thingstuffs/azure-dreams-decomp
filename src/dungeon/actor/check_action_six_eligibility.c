#include "common.h"
#include "shared/entity.h"

s16 attempt_action_six_if_eligible();               /* extern */


/* Test whether the target lookup with record-derived parameters is nonnegative. */
u32 check_action_six_eligibility(EntityRec *record, s32 target) {
    u8 scale;

    scale = (*(u8 *)((u8 *)&record->unk_10 + 1));
    return (u32) ~attempt_action_six_if_eligible(target, scale * 4, (scale >> 2) + 0x10) >> 0x1F;
}
