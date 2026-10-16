#include "common.h"
#include "m2c_compat.h"

void townDispatchItemMenuEntryCallback();                         /* extern */

/* Calls townDispatchItemMenuEntryCallback with the offset increased by 0x20. */
void townInvokeItemMenuOffsetHandler(s32 offset) {
    townDispatchItemMenuEntryCallback(offset + 0x20);
}
