#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 townGetLinkedRecordField2D60();                            /* extern */

/* Read the current state value and discard the result. */
void townReadCurrentStateValue(void) {
    townGetLinkedRecordField2D60();
}
