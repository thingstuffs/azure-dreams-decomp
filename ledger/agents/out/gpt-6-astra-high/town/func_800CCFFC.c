#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800CA214;

typedef struct S_800CA75C_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x14];
    s16 unk_6C;
} S_800CA75C_0;   /* arg0 in func_800CA75C */

/* Set the object's data pointer and state to 13. */
void func_800CA75C(S_800CA75C_0 *object) {
    object->unk_54 = &D_800CA214;
    object->unk_6C = 0xD;
}
