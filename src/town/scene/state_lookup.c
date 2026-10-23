/* State lookup with entry predicate overrides
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00638 - CL:town/func_8046F1C8, CL:town/func_8046F224, CL:town/image_3ef000@3EF164.
 * CL:town/func_8046F1C8
 * CL:town/func_8046F224
 * CL:town/image_3ef000@3EF164
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* State lookup with entry predicate overrides */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00638 - CL:town/func_8046F1C8, CL:town/func_8046F224, CL:town/image_3ef000@3EF164. */

#include "modules/town_ovl_3ef1c8.h"
#include "script_symbols.h"

s32 check_any_entry_matches_predicate(void) {
    u8 *entry = &D_8001A92C;

    if (D_8001A92C != 0) {
        do {
            if (town_table_contains_first_byte_b(*entry) != 0) {
                return 1;
            }
            entry++;
        } while (*entry != 0);
    }
    return 0;
}

/* Runs three flag handlers once the required flag is set and the shared completion flag is clear. */
s32 lookup_variant_with_special_overrides(s32 requiredFlag, s32 completionFlag) {
    if (func_8001A510(requiredFlag) == 0) {
        return 1;
    }
    if (func_8001A510(F_sbs22_pad39) != 0) {
        return 1;
    }
    func_8001A418(F_sbs22_pad39);
    func_8001A418(completionFlag);
    func_8001A490(requiredFlag);
    return 0;
}

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
