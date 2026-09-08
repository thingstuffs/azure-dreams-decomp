#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E670();                         /* extern */
extern s16 D_8001797C;

/* Passes the value of D_8001797C to func_8001E670. */
void func_8001C5A4(void) {
    func_8001E670(D_8001797C);
}
