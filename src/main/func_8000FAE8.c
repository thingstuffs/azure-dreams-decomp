#include "common.h"
#include "m2c_compat.h"

void cardBootCenterMessageDialogDisplay();                         /* extern */
void *cardBootBuildPairedDialogPackets();                    /* extern */

/* Processes the embedded data and then updates the record. */
void cardBootInitializeDialogPacketsAndDisplay(s32 record) {
    cardBootBuildPairedDialogPackets(record + 0x24, record);
    cardBootCenterMessageDialogDisplay(record);
}
