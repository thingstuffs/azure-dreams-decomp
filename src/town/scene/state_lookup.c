/* State lookup with entry predicate overrides
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8046F1C8, CL:town/func_8046F224, CL:town/image_3ef000@3EF164.
 * town/func_8046F1C8
 * town/func_8046F224
 * town/image_3ef000@3EF164
 */
#include "town/scene.h"

/* Private declarations retained from the member sources. */
/* State lookup with entry predicate overrides */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8046F1C8, CL:town/func_8046F224, CL:town/image_3ef000@3EF164. */

#include "modules/town_ovl_3ef1c8.h"
#include "script_symbols.h"
#include "town/scene/response_checks.h"
#include "town.h"
#include "town/player/state.h"
#include "town/player.h"

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
    if (get_script_flag_mask(requiredFlag) == 0) {
        return 1;
    }
    if (get_script_flag_mask(F_sbs22_pad39) != 0) {
        return 1;
    }
    set_script_flag_bit(F_sbs22_pad39);
    set_script_flag_bit(completionFlag);
    clear_script_flag_bit(requiredFlag);
    return 0;
}

/* Selects dialogue data from progress thresholds and lookup overrides, setting the associated flags. */
s32 *select_state_result_with_lookup_overrides(s32 first_value, s32 second_value, s32 unused_context) {
    s32 *result;
    s32 value;

    if (apply_scene_override_flag(first_value, second_value) != 0) {
        result = &D_8001EC04;
    } else {
        value = get_linked_record_field_2_d_60();
        if ((get_script_flag_mask(F_sbs22_pad30) == 0) && ((value < 5) || (lookup_variant_with_special_overrides(0x47E, 0x79A) != 0))) {
            result = &D_8001E2F8;
            set_script_flag_bit(F_sbs04_pad08);
        } else if ((get_script_flag_mask(F_sbs22_pad31) == 0) && ((value < 0xA) || (lookup_variant_with_special_overrides(0x47E, 0x79B) != 0))) {
            result = &D_8001E634;
            set_script_flag_bit(F_sbs04_pad08);
        } else if ((get_script_flag_mask(F_sbs22_pad32) == 0) && ((value < 0xF) || (lookup_variant_with_special_overrides(0x47E, 0x79C) != 0))) {
            result = &D_8001E79C;
            set_script_flag_bit(F_sbs04_pad08);
        } else if ((get_script_flag_mask(F_sbs22_pad33) == 0) && (((value < 0x19) && (check_any_entry_matches_predicate() != 0))
            || (lookup_variant_with_special_overrides(0x47E, 0x79D) != 0))) {
            result = &D_8001E9C0;
            set_script_flag_bit(F_sbs04_pad08);
        } else {
            result = &D_8001EB10;
        }
        set_script_flag_bit(F_sbs22_pad39);
    }
    return result;
}
