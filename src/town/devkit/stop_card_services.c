#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"


/* Run the three callbacks in sequence. */
void stop_card_services(void) {
    StopCARD2_804087B8();
    func_80408958();
    func_804087C8();
}
