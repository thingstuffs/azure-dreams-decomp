#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80098160;

typedef struct S_80098CD8_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x8];
    s16 unk_10;
} S_80098CD8_0;   /* arg0 in func_80098CD8 */

/* Initialize the object's data pointer and set its initial value to 0x400. */
void func_80098CD8(S_80098CD8_0 *object) {
    object->unk_04 = &D_80098160;
    object->unk_10 = 0x400;
}
