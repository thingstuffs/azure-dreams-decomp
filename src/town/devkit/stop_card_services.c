#include "common.h"
#include "town/devkit.h"
#include "frontend/card/server_imports.h"


/* Run the three callbacks in sequence. */
void stop_card_services(void) {
    StopCARD2_804087B8();
    swap_card_bios_patch_80408958();
    _ExitCard_804087C8();
}
