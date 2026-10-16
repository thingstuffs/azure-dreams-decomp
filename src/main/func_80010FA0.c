#include "common.h"
#include "m2c_compat.h"

void cardBootInitializeSlotWindowFrame();      /* extern */
void cardBootPopulateSlotWindowDisplay();                         /* extern */
void cardBootSetSlotIndexAndOwner(s32, s32, s32);                            /* extern */

/* Configures the record, processes its embedded data, and updates the record. */
void cardBootInitializeSlotWindow(s32 record, s32 setup_value, s32 processing_value) {
    cardBootSetSlotIndexAndOwner(record, setup_value, processing_value);
    cardBootInitializeSlotWindowFrame(record + 0x24C, record + 0x224, record + 0x234, processing_value);
    cardBootPopulateSlotWindowDisplay(record);
}
