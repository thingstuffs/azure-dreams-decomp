#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"


/* Run the setup sequence using the supplied context. */
void init_card_services(void *context) {
    ChangeClearPAD_8007CB08(0);
    EnterCriticalSection_8007CA38();
    InitCARD2_80408798(context);
    install_card_bios_patch_804088A0();
    swap_card_bios_patch_80408958();
    ExitCriticalSection_8007CA48();
}
