#include "common.h"
#include "m2c_compat.h"

void townProcessLshopEntries(s32, s32);             /* extern */

/* Calls townProcessLshopEntries with the supplied value and a zero second argument. */
void townProcessLshopValue(s32 value) {
    townProcessLshopEntries(value, 0);
}
