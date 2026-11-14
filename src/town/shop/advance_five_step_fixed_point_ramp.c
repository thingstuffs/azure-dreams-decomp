#include "common.h"
#include "m2c_compat.h"
#include "town/shop.h"
#include "shared/object_node.h"

/* Advance the five-step fixed-point ramp and switch callbacks after the final step. */
void advance_five_step_fixed_point_ramp(void *sub_object) {
    ShopRecordResetObject *object = sub_object;
    s32 next_step;

    object->step_resources->ramp = (s16)((object->ramp_step << 0xC) / 5);
    next_step = object->ramp_step + 1;
    object->ramp_step = next_step;
    if (next_step >= 6) {
        NODE_HEADER(sub_object)->update_callback = &fade_menu_side_indicators;
    }
}
