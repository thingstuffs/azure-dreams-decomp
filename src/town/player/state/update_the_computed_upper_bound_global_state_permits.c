#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 handle_query_position_after_subtracting_global_z_offset(EntityRec *);                                /* extern */
void set_the_clear_secondary_refresh_global_flag_set();                 /* extern */
extern s32 D_800FE5D4;


/* Update the record to the computed upper bound when the global state permits. */
void update_the_computed_upper_bound_global_state_permits(EntityRec *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (handle_query_position_after_subtracting_global_z_offset(record) << 0x10) - 1;
        if (upper_bound >= record->z.v) {
            set_the_clear_secondary_refresh_global_flag_set(record, upper_bound);
        }
    }
}
