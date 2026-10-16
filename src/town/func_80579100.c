#include "modules/town_ovl_4f9100.h"

void townInvokeCallbackAndSetSharedPointer(void) {
    TownStateRecord *activeState;
    s32 valueBeforeClamp;

    activeState = D_80016000->unk_38;
    valueBeforeClamp = activeState->unk_35C0;
    D_800175B8 = &D_80017500;
    if (valueBeforeClamp < 0x1E) {
        activeState->unk_35C0 = 0x1E;
    }
    func_80017398(0x5D9, activeState);
    func_80017398(0x5DA);
    D_800175B4 = 0;
    func_80017398(0x5DB);
}
