#include "common.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town/scene.h"

extern s32 grandpa_house_two_override_response_entries;
extern u8 D_80019104[];
extern u8 D_800197D0[];
extern u8 D_80019397[];

/* Looks up an entry and substitutes special results for codes 0x2D and 0x2F. */
void *select_response_with_two_overrides(TownObjectSet *input, s32 unused_1, s32 input_code, s32 unused_3) {
    s32 code;
    void *result;

    code = input_code;
    {
        void *lookup_data = &grandpa_house_two_override_response_entries;

        result = apply_entry_position(lookup_data, D_80019104, input, code);
        if (code == 0x2D) {
            if (resolve_entry_flag(lookup_data, input, 0x2D) != 0) {
                return D_800197D0;
            }
        }
    }
    if (code == 0x2F) {
        if (resolve_entry_flag(&grandpa_house_two_override_response_entries, input, 0x2F) != 0) {
            return D_80019397;
        }
    }
    return result;
}
