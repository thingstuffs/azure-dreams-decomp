#include "common.h"
#include "town/scene/script_hooks.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80019438;
s32 func_80016B20(void *entry, s32 callback_mode);              /* extern */
extern M2C_UNK D_80019440;

/* Update D_80019438 with the result of func_80016B20(&D_80019440, 1). */
s32 update_result_1(void) {
    return D_80019438 = func_80016B20(&D_80019440, 1);
}
