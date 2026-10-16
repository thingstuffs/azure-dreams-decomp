#include "common.h"
#include "m2c_compat.h"

void townSetReferencedObjectActiveFlag();                            /* extern */
void townSetScriptFlagBit();                     /* extern */

/* Runs townSetScriptFlagBit with code 0x1452 and its townSetReferencedObjectActiveFlag follow-up. */
void townProcessEvent1452AndRefresh(void) {
    townSetScriptFlagBit(0x1452);
    townSetReferencedObjectActiveFlag();
}
