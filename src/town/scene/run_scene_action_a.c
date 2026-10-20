#include "script_symbols.h"
#include "common.h"
void func_80018ADC(s32);                     /* extern */

/* Calls func_80018ADC with the fixed value 0x5A4. */
void run_scene_action_5_a_4(void) {
    func_80018ADC(F_sbs11_pad01);
}
