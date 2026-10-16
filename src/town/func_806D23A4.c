#include "common.h"

extern u8 D_800160B8[9];
extern u8 D_80016E3C[9];
extern void townProcessFlagTestRecord(void *, void *, void *, void *);

/* Apply the selected record from the fixed tables to the context. */
void townApplySelectedFixedRecord(void *context, s32 unused, void *selector)
{
    townProcessFlagTestRecord(D_800160B8, D_80016E3C, context, selector);
}
