#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 func_8001E578(s32, ...);
extern M2C_UNK D_800227C5;

/* Calls func_8001E578 with 0x400 and returns the address of D_800227C5. */
s32 *load_resource_400_secondary_buffer(void) {
    func_8001E578(F_sbs01_pad11);
    return &D_800227C5;
}
