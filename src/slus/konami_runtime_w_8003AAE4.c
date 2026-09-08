#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AAE4_0 {
    u8 pad_00[0xAC];
    s16 unk_AC;
    s16 unk_AE;
} S_8003AAE4_0;   /* base in func_8003AAE4 */


extern u8 D_80082A38[];

/* Store two signed 16-bit values in the runtime state. */
void func_8003AAE4(s16 value_ac, s16 value_ae) {
    u8 *state;

    state = D_80082A38;
    ((S_8003AAE4_0 *)state)->unk_AC = value_ac;
    ((S_8003AAE4_0 *)state)->unk_AE = value_ae;
}
