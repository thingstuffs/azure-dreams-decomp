#include "common.h"
#include "shared/entity.h"
#include "m2c_compat.h"

s32 get_probe_min_result(ObjectPosition *);                           /* extern */
s16 get_probe_max_result(ObjectPosition *input);                           /* extern */
struct EntityRec; void set_player_x_and_sync_collision(ObjectPosition *, s32);                  /* extern */
struct EntityRec; void set_global_800_cfcea_initialize_call_callee_800954_c_4(struct EntityRec *, s32);                  /* extern */
#include "town/player/probe_offset_data.h"

/* Applies fixed-point boundary corrections according to D_800FE5CC. */
void clamp_x_to_probe_bounds(ObjectPosition *position) {
    s32 upper_bound;
    s32 neutral_upper_bound;
    s32 lower_bound;

    if (town_primary_probe_offset > 0) {
        upper_bound = get_probe_min_result(position) << 0x10;
        if (position->x.v >= upper_bound) {
            set_player_x_and_sync_collision((position), upper_bound);
            return;
        }
    } else {
        if (town_primary_probe_offset >= 0) {
            neutral_upper_bound = get_probe_min_result(position) << 0x10;
            if (position->x.v >= neutral_upper_bound) {
                set_player_x_and_sync_collision((position), neutral_upper_bound);
            }
        }
        lower_bound = (get_probe_max_result(position) << 0x10) - 1;
        if (lower_bound >= position->x.v) {
            set_global_800_cfcea_initialize_call_callee_800954_c_4((struct EntityRec *)(position), lower_bound);
        }
    }
}
