#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Forwards the value to cardBootCreateOrResetMessageDialog with mode 3 and zeroed trailing arguments. */
void cardBootShowDamagedMemoryCardNotice(s32 value) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(value, 3, zero, zero);
}
