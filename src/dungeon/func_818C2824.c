#include "common.h"

typedef struct {
    u8 pad00[0x28];
    u8 flags;
    u8 pad29[0x3B];
    u16 value64;
} Obj;

extern s32 dungeonTryTriggerTargetRecordEffect(Obj *, s32);
extern s32 func_800A6870(s16 input_value);
extern void dungeonCapPendingActorValueDelta(Obj *);
extern void createActorValuePopup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern void dungeonApplyClampedActorValueDelta(Obj *);

/* Applies a flag-adjusted value increase and updates the target. */
void func_818C2824(Obj *target, s32 amount_param)
{
    s32 base_amount;
    register s32 adjusted_amount;

    if (dungeonTryTriggerTargetRecordEffect(target, 4) == 0) {
        base_amount = func_800A6870(amount_param & 0xFF) + 0x10;
        adjusted_amount = base_amount;
        if (target->flags & 1) {
            adjusted_amount = base_amount + ((s16)base_amount >> 1);
        }
        target->value64 += adjusted_amount;
        dungeonCapPendingActorValueDelta(target);
        base_amount = 0x8004;
        createActorValuePopup(base_amount, target, (s16)target->value64, 1);
        dungeonApplyClampedActorValueDelta(target);
    }
}
