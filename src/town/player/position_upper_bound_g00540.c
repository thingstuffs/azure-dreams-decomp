/* position upper bound. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80099028, CL:town/func_80099080, PD:town/engine:800FE5D4. */
#include "town/player/position_upper_bound_g00540.h"
#include "town/player.h"

/*
 * Subtracts D_800FE5D4 from a copy of Z and returns max_adjusted_z_query over four entries from
 * D_800D040C.
 */
s32 query_position_upper_bound(ObjectPosition *position) {
    LocalVec pos;

    pos.x = (u32)position->x.v;
    pos.y = position->y.v;
    pos.z = position->z.v - D_800FE5D4;
    return max_adjusted_z_query(&pos, D_800D040C[0], 4);
}

/* Set the record value, clear its secondary value, and refresh it with the global flag set. */
void set_player_z_and_sync_collision(ObjectPosition *record, s32 value) {
    D_800CFCE8 = 1;
    record->z.v = value;
    record->velocity_z = 0;
    copy_z_to_collision_motion(record);
}

/* Update the record to the computed upper bound when the global state permits. */
void update_position_upper_bound(ObjectPosition *record) {
    s32 upper_bound;

    if (D_800FE5D4 < 0) {
        upper_bound = (query_position_upper_bound((record)) << 0x10) - 1;
        if (upper_bound >= record->z.v) {
            set_player_z_and_sync_collision(record, upper_bound);
        }
    }
}
