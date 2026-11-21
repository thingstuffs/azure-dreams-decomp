#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

void libcard_stop(void) {
    StopCARD2_804087B8();
    swap_card_bios_patch_80408958();
    _ExitCard_804087C8();
}
