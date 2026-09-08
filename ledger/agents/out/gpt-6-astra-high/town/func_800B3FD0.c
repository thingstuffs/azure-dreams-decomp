#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_800B1730_0 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B1730_0;   /* arg0 in func_800B1730 */

/* Sets the object's field at offset 0x24 to one. */
void func_800B1730(S_800B1730_0 *object) {
    object->unk_24 = 1;
}
