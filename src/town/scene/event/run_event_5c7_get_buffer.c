#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player/script_flags.h"
#include "town/scene/event.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80020B64;

/* Pass 0x5C7 to func_80018A64 and return the address of D_80020B64. */
s32 *run_event_5c7_get_buffer(void) {
    func_80018A64(F_sbs11_pad36);
    return &D_80020B64;
}
