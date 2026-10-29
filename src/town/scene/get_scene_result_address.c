#include "common.h"
#include "town/scene.h"

extern u8 D_8001C769[];
extern u8 D_8001D244[];

/* Returns the shared result address when the input check succeeds. */
void *get_scene_result_address(s32 check_input_a, s32 check_input_b, s32 check_input_c) {
    if (lookup_with_override_fallback(check_input_a, check_input_b, check_input_c) != 0) {
        return D_8001D244;
    }
    return D_8001C769;
}
