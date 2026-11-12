#include "common.h"
#include "town/scene/mode_data.h"

extern s32 * select_fallback_when_below_threshold(void *input); /* placed copy of select_fallback_when_below_threshold */

extern void *D_80019698[3];
extern u8 D_8001A730[9];
extern u8 scene_selector_one_mode_three_data[9];
extern u8 scene_selector_one_default_data[9];

/* Returns data selected by kind and the current global index. */
void *select_data_by_kind_and_index(void *unused_0, s32 unused_1, s32 data_kind) {
    void *data = 0;

    if (data_kind == 8) {
        data = select_fallback_when_below_threshold(D_80019698[scene_dispatch_mode_index]);
    } else if (data_kind == 6) {
        data = D_8001A730;
    } else if (data_kind == 1) {
        if (scene_dispatch_mode_index != 3) {
            data = scene_selector_one_default_data;
        } else {
            data = scene_selector_one_mode_three_data;
        }
    }

    return data;
}
