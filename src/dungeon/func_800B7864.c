#include "common.h"

extern u8 D_80082E6B;
extern s16 D_8008146C;
extern u8 D_800DCF4E[];
extern u8 D_800DF3CC[];

extern s32 func_80033BC0(s32);
extern void func_80040AA0(s32);
extern void Control_CD();
extern void drain_cd_command_queue(void);

/* Invokes action 0x21 once when its conditions hold, or runs the default action. */
void invoke_action_21_or_default(void) {
    s32 *state_flags;

    if (D_80082E6B == 0x11) {
        state_flags = (s32 *)0x80010000;
        if (state_flags[0x824] == 0 && D_8008146C == 0x28 &&
            func_80033BC0(0xa2) == 0 && state_flags[0x823] == 0) {
            state_flags[0x823] = 1;
            func_80040AA0(0x21);
            D_800DCF4E[0] = 0;
            return;
        }
    }
    Control_CD(6, &D_800DF3CC, 0);
    drain_cd_command_queue();
}
