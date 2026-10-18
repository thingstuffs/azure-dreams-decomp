#include "common.h"

extern u8 D_800160B8[9];
extern u8 D_80016E3C[9];
extern void process_flag_test_record(void *, void *, void *, void *);

/* Apply the selected record from the fixed tables to the context. */
void apply_selected_fixed_record(void *context, s32 unused, void *selector)
{
    process_flag_test_record(D_800160B8, D_80016E3C, context, selector);
}
