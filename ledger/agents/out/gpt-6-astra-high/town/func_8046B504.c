#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E670();                         /* extern */
extern s16 D_80017968;

/* Pass the current value of D_80017968 to func_8001E670. */
void func_8001C504(void) {
    func_8001E670(D_80017968);
}
