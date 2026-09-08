#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80018ADC();                     /* extern */

/* Calls func_80018ADC with the fixed value 0x5A4. */
void func_80016EA8(void) {
    func_80018ADC(0x5A4);
}
