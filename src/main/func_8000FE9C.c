#include "common.h"
#include "m2c_compat.h"

u8 *cardBootCreateOrResetMessageDialog();   /* extern */

/* Initialize the context in mode 1 with zero optional arguments. */
void cardBootShowNoMemoryCardNotice(s32 context) {
    s32 zero = 0;
    cardBootCreateOrResetMessageDialog(context, 1, zero, zero);
}
