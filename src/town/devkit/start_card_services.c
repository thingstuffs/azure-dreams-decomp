#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"

/* Start card services inside a critical section. */
void start_card_services(void) {
    EnterCriticalSection_8007CA38();
    StartCARD2_804087A8();
    ChangeClearPAD_8007CB08(0);
    ExitCriticalSection_8007CA48();
}
