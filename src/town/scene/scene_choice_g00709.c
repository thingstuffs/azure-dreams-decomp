/* Select scene choices and set interaction flags (G00709). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80470C64, CL:town/func_80470D04. */
#include "town/scene/scene_choice_g00709.h"
#include "town/scene.h"
#include "town/player/state.h"

/* Calls func_8001A418 with F_sbs22_pad34. */
void invoke_handler_with_code_79_e(void) {
    set_script_flag_bit(F_sbs22_pad34);
}

void select_scene_choice_by_mode(void)
{
    void *choices[2] = { &D_8001AB94, &D_8001ABE8 };
    void *town = *(void **)((s8 *)*(void **)((s8 *)(&town_scene_root)) + 0x40);

    invoke_alternate_handler_with_code_780();
    invoke_handler_with_code_79_e();
    if (get_script_flag_mask(D_8001A91E) == 0) {
        clear_script_flag_bit(F_sbs22_pad39);
    }
    D_8001B320 = choices[*(s32 *)((s8 *)town + 0xB0)];
}
