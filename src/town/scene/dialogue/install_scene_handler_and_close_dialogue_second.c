#include "common.h"
#include "town/scene/motion.h"

extern u8 D_80017A18[9];
extern u8 D_80017B5C[9];
extern u8 D_80018AE5[9];

extern s32 query_referenced_flag_for_table_entry(void *, void *, s32);
extern s32 get_script_flag_mask(s32 flag_index); /* placed copy of get_script_flag_mask */

/* Selects a result for the context, applying an override when both checks pass. */
void *select_checked_table_pointer(void *context, s32 unused, s32 mode)
{
    void *result;

    result = apply_entry_position(D_80017A18, D_80017B5C, context, mode);
    if (query_referenced_flag_for_table_entry(D_80017A18, context, mode) != 0) {
        if (get_script_flag_mask(*(s16 *)((u8 *)context + 0x18)) != 0) {
            result = D_80018AE5;
        }
    }
    return result;
}
