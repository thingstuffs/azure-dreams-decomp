#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"

extern void func_800197D8(s32);
extern void func_80019850(s32);
extern s32 func_800198D0(s32);
extern s32 scene_update_state;

/* Set state 5 and apply the two updates when check 0x145D succeeds. */
s32 set_state_five_and_apply_updates(void) {
    scene_update_state = 5;
    if (func_800198D0(F_sero_end) != 0) {
        func_800197D8(F_niko_selro_asa);
        func_80019850(Fp_niko_kenkatyu);
        return 0;
    }
    return 1;
}
