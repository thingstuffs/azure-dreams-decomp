#include "script_symbols.h"
#include "common.h"

extern void func_80017320(s32);
extern void func_80017398(s32);
extern s16 scene_threshold_counter;

/* Advance the counter D_800175B4 (wrapping from 21 back to 9); at 8 or 20 call func_80017320(0x5DB), else func_80017398(0x5DB). */
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
