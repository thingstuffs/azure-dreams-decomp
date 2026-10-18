#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 process_global();                     /* extern */

typedef struct S_8001B93C_0 {
    u8 pad_00[0x20];
    s32 * unk_20;
} S_8001B93C_0;   /* arg0 in func_8001B93C */

/* Call process_global with zero when the referenced value is zero. */
void func_8001B93C(S_8001B93C_0 *object) {
    if (*object->unk_20 == 0) {
        process_global(0);
    }
}
