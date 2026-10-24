#include "common.h"

#include "town/scene.h"
extern s32 town_repeat_value_selected;
extern s32 scene_choice_index;

/* Returns a helper result or a value from the first-use or subsequent-use table. */
void *select_first_or_later_use_value(s32 unused_0, s32 unused_1, s32 selector) {
    if (selector == 1) {
        return return_zero_event_value(scene_choice_index);
    }
    if (town_repeat_value_selected == 0) {
        void **first_table = D_800166F8;

        town_repeat_value_selected = 1;
        return first_table[scene_choice_index];
    }
    {
        void **repeat_table = D_80016718;
        return repeat_table[scene_choice_index];
    }
}
