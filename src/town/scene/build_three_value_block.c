#include "common.h"
#include "town/scene.h"
#include "town/scene/motion.h"

extern s32 D_80017AAC[];
extern s32 scene_first_component_values[];
extern s32 scene_second_component_values[];
extern s32 D_80017CA0[];

/* Apply three value tables to consecutive destinations and return their base. */
s32 build_three_value_block(void) {
    s32 *base_ptr = D_80017CA0;

    copy_callback_value_to_destination(base_ptr[0], D_80017AAC);
    copy_callback_value_to_destination(base_ptr[0] + 0x14, scene_first_component_values);
    copy_callback_value_to_destination(base_ptr[0] + 0x28, scene_second_component_values);
    return base_ptr[0];
}
