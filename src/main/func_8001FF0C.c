#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8001FF0C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8001FF0C_0;   /* arg0 in func_8001FF0C */

/* Sets the object's field at offset 0x20 to the supplied value. */
void func_8001FF0C(S_8001FF0C_0 *object, s32 value) {
    object->unk_20 = value;
}
