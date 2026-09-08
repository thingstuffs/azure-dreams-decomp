#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80025480;

typedef struct S_80025514_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
} S_80025514_0;   /* arg0 in func_80025514 */

/* Set the object's data pointer to D_80025480. */
void func_80025514(S_80025514_0 *object) {
    object->unk_10 = &D_80025480;
}
