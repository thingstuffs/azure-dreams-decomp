#include "script_symbols.h"
#include "town/scene/hooks/invoke_callback_and_set_shared_pointer_second.h"
#include "town/scene/hooks/invoke_callback_and_set_shared_pointer_second.h"

void invoke_callback_and_set_shared_pointer(void) {
    TownStateRecord *activeState;
    s32 valueBeforeClamp;

    activeState = D_80016000->unk_38;
    valueBeforeClamp = activeState->unk_35C0;
    D_800175B8 = &D_80017500;
    if (valueBeforeClamp < 0x1E) {
        activeState->unk_35C0 = 0x1E;
    }
    func_80017398(F_sbs12_pad11, activeState);
    func_80017398(F_sbs12_pad12);
    D_800175B4 = 0;
    func_80017398(F_sbs12_pad13);
}
