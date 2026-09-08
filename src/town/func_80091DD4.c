#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct S_8008F534_0 {
    u8 pad_00[0x39];
    s8 unk_39;
} S_8008F534_0;   /* arg0 in func_8008F534 */

typedef struct S_8008F534_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
} S_8008F534_1;   /* arg1 in func_8008F534 */

/* Set the object flag, store the state value, and clear the state's secondary field. */
void func_8008F534(S_8008F534_0 *object, S_8008F534_1 *state, s32 value) {
    object->unk_39 = 1;
    state->unk_04 = value;
    state->unk_10 = 0;
}
