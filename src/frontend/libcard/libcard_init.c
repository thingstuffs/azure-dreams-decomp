#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_init(s32 slot) {
    ChangeClearPAD_8007CB08(0); EnterCriticalSection_8007CA38(); InitCARD2_80408798(slot);
    install_card_bios_patch_804088A0(); swap_card_bios_patch_80408958(); ExitCriticalSection_8007CA48();
}
