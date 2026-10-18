#include "common.h"

extern s32 get_script_flag_mask(s32 flagIndex);
extern u8 D_8001EC4B[];
extern u8 D_8001EB04[];

/* Select D_8001EB04 or D_8001EC4B based on the query for 0xD83. */
void *scale_record_value_and_add_offset(void) {
    if (get_script_flag_mask(0xD83) == 0) {
        return D_8001EB04;
    }
    return D_8001EC4B;
}
