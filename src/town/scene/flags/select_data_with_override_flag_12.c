#include "common.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town.h"

extern u8 D_800176AC[9];
extern u8 D_80017778[9];
extern u8 D_80018ED1[9];

/* Select a result and override it when condition 12 is active. */
void *select_data_with_override_flag_12(s32 selection_value, s32 unused, s32 selection_mode) {
    void *result;

    result = apply_entry_position(D_800176AC, D_80017778, selection_value, selection_mode);
    if (town_table_contains_first_byte_b(12) != 0) {
        result = D_80018ED1;
    }
    return result;
}
