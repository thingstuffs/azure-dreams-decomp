#include "modules/town_door.h"

void townSelectTowerEntryHandlerByItemCount(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params) {
    if (townCheckDoorInputAndAngle(script_state, unused_context) != 0) {
        if (townCountConsecutiveNonzeroEntriesUpTwenty() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &townUpdateDoorCompletionState;
            func_8009A8EC(script_state->unk_72, event_params->unk_02, event_params->unk_06);
            return;
        }
        script_state->unk_50 = &townSetDoorHandlerIfReady;
        townSetPlayerBlockValue(script_state->unk_72);
    }
}
