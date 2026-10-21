/* G00540: position upper bound. */
/* Original-file evidence (G00540): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80099028, CL:town/func_80099080, PD:town/engine:800FE5D4. */
#include "town/player/position_upper_bound_g00540.h"

/* Query the position after subtracting the global Z offset. */
s32 handle_query_position_after_subtracting_global_z_offset(Vec3i *position) {
    LocalVec pos;

    pos.x = position->x;
    pos.y = position->y;
    pos.z = position->z - D_800FE5D4;
    return max_adjusted_z_query(&pos, D_800D040C[0], 4);
}

/* Set the record value, clear its secondary value, and refresh it with the global flag set. */
void set_the_clear_secondary_refresh_global_flag_set(EntityRec *record, s32 value) {
    D_800CFCE8 = 1;
    record->z.v = value;
    record->flags14 = 0;
    clear_global_slot_n_5_copy_source_slot_n_2_global_slot_n_2(record);
}

/* Update the record to the computed upper bound when the global state permits. */
void update_the_computed_upper_bound_global_state_permits(EntityRec *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (handle_query_position_after_subtracting_global_z_offset((Vec3i *)record) << 0x10) - 1;
        if (upper_bound >= record->z.v) {
            set_the_clear_secondary_refresh_global_flag_set(record, upper_bound);
        }
    }
}
