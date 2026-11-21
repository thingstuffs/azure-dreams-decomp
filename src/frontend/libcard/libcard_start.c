#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_start(void) {
    EnterCriticalSection_8007CA38();
    StartCARD2_804087A8();
    ChangeClearPAD_8007CB08(0);
    ExitCriticalSection_8007CA48();
}
