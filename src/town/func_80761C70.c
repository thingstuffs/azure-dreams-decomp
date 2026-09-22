#include "common.h"

extern u8 D_80017A20[9];
extern u8 D_80017B5C[9];
extern u8 D_80018CC0[9];
extern u8 D_80018D9F[9];
extern u8 D_80018E42[9];

extern void *func_80016F14(void *, void *, void *, s32);
extern s32 func_80016EB8(void *, void *, s32);
extern void func_8001779C(u16);
extern s32 func_8001781C(s16);
extern s32 func_80017948(s32);

/* Look up the slot's record, substituting fixed records when it is claimed or the 7-flag is set. */
void *func_80761C70(void *slot, s32 unused, s32 context)
{
    void *result;

    result = func_80016F14(D_80017A20, D_80017B5C, slot, context);
    if (func_80016EB8(D_80017A20, slot, context) != 0) {
        if (func_8001781C(0x9E9) != 0) {
            result = D_80018D9F;
        } else {
            result = D_80018CC0;
        }
    } else {
        func_8001779C(0x9E9);
    }
    if (func_80017948(7) != 0) {
        result = D_80018E42;
    }
    return result;
}
