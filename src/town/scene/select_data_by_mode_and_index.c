#include "script_symbols.h"
#include "common.h"

extern s32 check_inputs_after_threshold_two(s32);
extern void func_800193E0(s32);

extern s32 scene_dispatch_mode_index;
extern s32 D_80019760[];
extern u8 scene_selector_one_mode_three_data[];
extern u8 scene_selector_one_default_data[];
extern u8 D_80020C9C[];

/* Selects mode-specific data for selectors 1 and 3, or runs the selector-8 check and event. */
s32 select_data_by_mode_and_index(void *unused0, s32 unused1, s32 selector) {
    s32 result = 0;

    if (selector == 8) {
        result = check_inputs_after_threshold_two(D_80019760[scene_dispatch_mode_index]);
        func_800193E0(Ft_paty_love);
    } else if (selector == 1) {
        if (scene_dispatch_mode_index != 3) {
            result = (s32)scene_selector_one_default_data;
        } else {
            result = (s32)scene_selector_one_mode_three_data;
        }
    } else if (selector == 3) {
        result = (s32)D_80020C9C;
    }

    return result;
}

/* MECHANISM: The row's two tail targets (true base +0x94 / +0x98) are its own epilogue; the plain
   `result` chain returning through one exit reproduces both entries. */
