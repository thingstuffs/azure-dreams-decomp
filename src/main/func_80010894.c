#include "common.h"
#include "m2c_compat.h"

void cardBootLayoutThreeRowCommandPanel();                         /* extern */
M2C_UNK func_80023730();               /* extern */
void func_8002388C();                            /* extern */

/* Prepares processing, processes the embedded data, and updates the record. */
void cardBootInitializeThreeRowCommandPanel(s32 record) {
    func_8002388C();
    func_80023730(record + 0x190, record + 0x168, record + 0x178);
    cardBootLayoutThreeRowCommandPanel(record);
}
