/* Action control dispatch (G00352). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800DCF4E. */
#include "dungeon/actor/action_control_dispatch_g00352.h"

/* Invokes action 0x21 once when its conditions hold, or runs the default action. */
void invoke_action_21_or_default(void) {
    s32 *state_flags;

    if (D_80082E6B == 0x11) {
        state_flags = (s32 *)0x80010000;
        if (state_flags[0x824] == 0 && D_8008146C == 0x28 &&
            test_resident_bit(0xa2) == 0 && state_flags[0x823] == 0) {
            state_flags[0x823] = 1;
            func_80040AA0(0x21);
            ((u8 *)&D_800DCF4E)[0] = 0;
            return;
        }
    }
    Control_CD(6, &D_800DF3CC, 0);
    drain_cd_command_queue();
}

void trigger_action_21_or_update_control(void) {
    if (D_80082E6B == 0x11) {
        SaveImage *save = (SaveImage *)0x80010000;
        if (save->active == 0 && D_8008146C == 0x28 &&
            test_resident_bit(0xA2) == 0 && save->pending == 0) {
            save->pending = 1;
            func_80040AA0(0x21);
            D_800DCF4E = 0;
            return;
        }
    }
    func_8003E4FC(6, D_800DF3D4, 0);
    func_8003F320();
}
