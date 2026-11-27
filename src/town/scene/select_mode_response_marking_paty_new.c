#include "script_symbols.h"
#include "common.h"
#include "town/scene/mode_data.h"
#include "town/player/state.h"
#include "town/scene.h"


extern void *restaurant_patty_new_mode_response_pointers[3];
extern u8 D_8001A730[9];
extern u8 scene_selector_one_mode_three_data[9];
extern u8 scene_selector_one_default_data[9];

/* Returns data for the request type and current selection. */
void *select_mode_response_marking_paty_new(s32 unused_0, s32 unused_1, s32 request_type) {
    void *result = 0;

    if (request_type == 8) {
        set_script_flag_bit(Ft_paty_new);
        result = select_fallback_when_below_threshold(restaurant_patty_new_mode_response_pointers[scene_dispatch_mode_index]);
    } else if (request_type == 6) {
        result = D_8001A730;
    } else if (request_type == 1) {
        if (scene_dispatch_mode_index != 3) {
            result = scene_selector_one_default_data;
        } else {
            result = scene_selector_one_mode_three_data;
        }
    }

    return result;
}
