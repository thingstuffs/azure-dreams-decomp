/* Select scene choices and set interaction flags (G00709). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_80470C64, CL:town/func_80470D04. */
#include "town/scene/scene_choice_g00709.h"

void invoke_handler_with_code_79_e(void) {
    func_8001A418(F_sbs22_pad34);
}

void select_scene_choice_by_mode(void)
{
    void *choices[2] = { &D_8001AB94, &D_8001ABE8 };
    void *town = *(void **)((s8 *)*(void **)((s8 *)(&D_80016000)) + 0x40);

    invoke_alternate_handler_with_code_780();
    invoke_handler_with_code_79_e();
    if (func_8001A510(D_8001A91E) == 0) {
        func_8001A490(F_sbs22_pad39);
    }
    D_8001B320 = choices[*(s32 *)((s8 *)town + 0xB0)];
}
