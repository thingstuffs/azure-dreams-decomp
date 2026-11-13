#include "shared/entity.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/scene/motion/offset_queries.h"
#include "town/scene/motion.h"

struct S_8008F534_0; struct S_8008F534_1; void stop_at_max_y(struct S_8008F534_0 *, struct S_8008F534_1 *, s32);             /* extern */
struct S_8008F548_0; void stop_at_min_y(struct S_8008F548_0 *, ObjectPosition *, s32);             /* extern */

/* Apply upper and lower boundary adjustments to a fixed-point value. */
void adjust_fixed_point_value_at_bounds(s32 context, s32 *value) {
    s32 upper_bound;
    s32 lower_bound;

    upper_bound = min_sampled_position_minus_y_offset(value) << 0x10;
    if (value[1] >= upper_bound) {
        stop_at_max_y((struct S_8008F534_0 *)(context), (struct S_8008F534_1 *)(value), upper_bound);
    }
    lower_bound = (query_position_with_second_component_offset(value) << 0x10) - 1;
    if (lower_bound >= value[1]) {
        stop_at_min_y((struct S_8008F548_0 *)(context), (ObjectPosition *)(value), lower_bound);
    }
}
