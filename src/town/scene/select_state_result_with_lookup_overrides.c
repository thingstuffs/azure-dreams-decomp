#include "script_symbols.h"
#include "modules/town_ovl_3ef1c8.h"

/* Selects dialogue data from progress thresholds and lookup overrides, setting the associated flags. */
s32 *select_state_result_with_lookup_overrides(s32 first_value, s32 second_value, s32 unused_context) {
    s32 *result;
    s32 value;

    if (func_80016164(first_value, second_value) != 0) {
        result = &D_8001EC04;
    } else {
        value = func_8001A7F8();
        if ((func_8001A510(F_sbs22_pad30) == 0) && ((value < 5) || (lookup_variant_with_special_overrides(0x47E, 0x79A) != 0))) {
            result = &D_8001E2F8;
            func_8001A418(F_sbs04_pad08);
        } else if ((func_8001A510(F_sbs22_pad31) == 0) && ((value < 0xA) || (lookup_variant_with_special_overrides(0x47E, 0x79B) != 0))) {
            result = &D_8001E634;
            func_8001A418(F_sbs04_pad08);
        } else if ((func_8001A510(F_sbs22_pad32) == 0) && ((value < 0xF) || (lookup_variant_with_special_overrides(0x47E, 0x79C) != 0))) {
            result = &D_8001E79C;
            func_8001A418(F_sbs04_pad08);
        } else if ((func_8001A510(F_sbs22_pad33) == 0) && (((value < 0x19) && (check_any_entry_matches_predicate() != 0))
            || (lookup_variant_with_special_overrides(0x47E, 0x79D) != 0))) {
            result = &D_8001E9C0;
            func_8001A418(F_sbs04_pad08);
        } else {
            result = &D_8001EB10;
        }
        func_8001A418(F_sbs22_pad39);
    }
    return result;
}
/* MECHANISM: The true-space CFG turns apparent configure_active_object_two_16/B0/B8 calls into local joins.
   One s0 result pointer reproduces the 0x18 frame and tail layout.
   Omitting check_any_entry_matches_predicate's explicit arg reuses the branch-delay a0 setup and closes word 58. */
