#include "script_symbols.h"
#include "common.h"

extern void func_80017320(s32);
extern void func_80017398(s32);
extern s16 scene_threshold_counter;

/*
 * Increments scene_threshold_counter and wraps 21 to 9; calls func_80017320 for F_sbs12_pad13 at
 * counts 8 and 20, or func_80017398 otherwise.
 */
void check_record_value_threshold(void) {
    scene_threshold_counter++;
    if (scene_threshold_counter >= 21) {
        scene_threshold_counter = 9;
    }
    if (scene_threshold_counter == 8 || scene_threshold_counter == 20) {
        func_80017320(F_sbs12_pad13);
    } else {
        func_80017398(F_sbs12_pad13);
    }
}
