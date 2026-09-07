#include "common.h"

typedef struct {
    u8 pad00[0x28];
    u8 flags;
    u8 pad29[0x3B];
    u16 value64;
} Obj;

extern s32 func_8009D218(Obj *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD568(Obj *, s32);
extern void func_800B4C7C(s32, Obj *, s16, s32);
extern void func_800AD4D0(Obj *);

/* Applies a flag-adjusted value increase and updates the target. */
void func_818C2824(Obj *target, s32 amount_param)
{
    register s32 base_amount ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */
    register s32 adjusted_amount;

    if (func_8009D218(target, 4) == 0) {
        base_amount = func_800A6870(amount_param & 0xFF) + 0x10;
        adjusted_amount = base_amount;
        if (target->flags & 1) {
            adjusted_amount = base_amount + ((s16)base_amount >> 1);
        }
        target->value64 += adjusted_amount;
        func_800AD568(target, adjusted_amount);
        func_800B4C7C(0x8004, target, (s16)target->value64, 1);
        func_800AD4D0(target);
    }
}
