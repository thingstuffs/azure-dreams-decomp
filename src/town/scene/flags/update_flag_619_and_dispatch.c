#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/flags.h"

extern s32 func_80018964(s32);
extern void func_800188E4(s32);
extern void *D_800190C0[];

/* Conditionally updates flag 0x619, then dispatches D_800190C0 to the callback. */
void change_map_after_flag_test(void) {
    if (func_80018964(Fp_bibian_pool) != 0) {
        func_800188E4(F_sbs13_pad32);
    }
    ((void (*)(void *))(*(void ***)((s8 *)town_scene_root + 0x20))[FNO_change_map])(D_800190C0);
}

/* MECHANISM: The call-shaped body naturally gives the 0x18 frame with only ra saved.
   The direct pointer/vtable load chain preserves the two dependent load-delay nops.
   Town's 2.7.2-cdk-G0 schedule places the page base and indirect-call argument exactly. */
