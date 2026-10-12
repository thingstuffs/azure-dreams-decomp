#include "common.h"

extern u8 D_800160B8[9];
extern u8 D_80016E3C[9];
extern void func_8001670C(void *, void *, void *, void *);

/* Apply the selected record from the fixed tables to the context. */
void func_80016058(void *context, s32 unused, void *selector)
{
    func_8001670C(D_800160B8, D_80016E3C, context, selector);
}
