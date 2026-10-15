#include "modules/town_door.h"

void func_800A0C30(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params) {
    if (func_800A0F10(script_state, unused_context) != 0) {
        if (func_8009F9A4() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &func_800A0CF8;
            func_8009A8EC(script_state->unk_72, event_params->unk_02, event_params->unk_06);
            return;
        }
        script_state->unk_50 = &func_800A0CC0;
        func_8009A99C(script_state->unk_72);
    }
}
