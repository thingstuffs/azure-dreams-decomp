#include "town/scene.h"
#include "script_symbols.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/resource.h"
#include "shared/town_root.h"
#include "town/player/state.h"
#include "town/scene/service.h"

extern void func_80019988(void); /* this scene's placed copy of set_current_entry_script_flag */

/* Run the three teardown passes; when the check fails, stop the scene object and report failure. */
s32 run_three_teardown_passes(s32 kind, s32 value)
{
    s32 result;

    set_script_flag_sbs32_pad34();
    init_okami_give_cape_state();
    func_80019988();
    if (apply_selected_entry_values(kind, value) == 0) {
        call_scene_service_2f4_fixed();
        ((void (*)(s32, s32))(town_scene_root->services->callback_2F8))(0xE, 0x200);
        result = 0;
    } else {
        set_script_flag_bit(F_sbs32_pad07);
        result = 1;
    }

    return result;
}

/* MECHANISM: True-space naming makes the apparent func_80017684 jump a local
   epilogue edge; a shared result local preserves the retail failure-first CFG.
   Two call-spanning arguments naturally occupy s0/s1, while the wide array
   declaration forces D_80016000 through its retail hi/lo access. */
