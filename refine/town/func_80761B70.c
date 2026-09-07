#include "common.h"

extern u8 D_80017A18[9];
extern u8 D_80017B5C[9];
extern u8 D_80018AE5[9];

extern void *func_80016F14(void *, void *, void *, s32);
extern s32 func_80016EB8(void *, void *, s32);
extern s32 func_8001781C(s16);

/* Selects a result for the context, applying an override when both checks pass. */
void *func_80761B70(void *context, s32 unused, s32 mode)
{
    void *result;

    result = func_80016F14(D_80017A18, D_80017B5C, context, mode);
    if (func_80016EB8(D_80017A18, context, mode) != 0) {
        if (func_8001781C(*(s16 *)((u8 *)context + 0x18)) != 0) {
            result = D_80018AE5;
        }
    }
    return result;
}
