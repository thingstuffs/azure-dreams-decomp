#include "common.h"
#include "m2c_compat.h"

void townProcessLshopEntries();                /* extern */

/* Forwards the base value plus four to townProcessLshopEntries with mode 1. */
void townProcessLshopValuePlusFour(s32 base_value) {
    townProcessLshopEntries(base_value + 4, 1);
}
