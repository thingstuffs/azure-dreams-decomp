#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void townAdvanceDispatchStateToTwo(void);                            /* extern */

/* Forward both inputs to townAdvanceDispatchStateToTwo. */
void townIgnoreInputsAndRunEventReset(s32 first_input, s32 second_input) {
    townAdvanceDispatchStateToTwo();
}
