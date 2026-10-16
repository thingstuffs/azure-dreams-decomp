#include "common.h"
#include "m2c_compat.h"

void cardBootPopulateSlotWindowDisplay();                         /* extern */
void func_800240EC();                         /* extern */
void cardBootClearTenDisplaySlots();                         /* extern */

/* Runs three update routines on the data of a non-null object. */
void cardBootRefreshSlotWindow(s32 object_addr) {
    s32 object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        func_800240EC(object_data);
        cardBootClearTenDisplaySlots(object_data);
        cardBootPopulateSlotWindowDisplay(object_data);
    }
}
