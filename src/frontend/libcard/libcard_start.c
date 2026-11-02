#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_start(void) {
    func_8007CA38();
    StartCARD2_804087A8();
    func_8007CB08(0);
    func_8007CA48();
}
