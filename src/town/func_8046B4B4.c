#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E670(s32);
extern s16 D_80017938;

/* Pass the current value of D_80017938 to func_8001E670. */
void apply_stored_value_17938(void) {
    func_8001E670(D_80017938);
}
