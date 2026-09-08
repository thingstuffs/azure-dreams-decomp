#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E670();                         /* extern */
extern s16 D_8001795C;

/* Pass the current value of D_8001795C to func_8001E670. */
void func_8001C554(void) {
    func_8001E670(D_8001795C);
}
