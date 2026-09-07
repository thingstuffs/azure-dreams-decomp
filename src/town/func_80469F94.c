#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_8001E578();                     /* extern */
extern M2C_UNK D_80023DB5;

M2C_UNK *func_8001AF94(void) {
    func_8001E578(0x400);
    return &D_80023DB5;
}
