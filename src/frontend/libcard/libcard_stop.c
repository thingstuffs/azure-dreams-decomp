#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_stop(void) {
    StopCARD2_804087B8();
    func_80408958();
    func_804087C8();
}
