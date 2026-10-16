#include "common.h"
#include "m2c_compat.h"

void townSetScriptFlagBit();                     /* extern */

/* Process IDs 0x1462, 0x1474, and 0xD89 in sequence. */
void townDispatchThreeProgressEvents(void) {
    townSetScriptFlagBit(0x1462);
    townSetScriptFlagBit(0x1474);
    townSetScriptFlagBit(0xD89);
}
