#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_8003AAE4_0 {
    u8 pad_00[0xAC];
    s16 unk_AC;
    s16 unk_AE;
} S_8003AAE4_0;   /* base in runtime_store_signed_state_pair */


extern u8 runtime_script_state[];

/* Store two signed 16-bit values in the runtime state. */
void runtime_store_signed_state_pair(s16 value_ac, s16 value_ae) {
    u8 *state;

    state = runtime_script_state;
    ((S_8003AAE4_0 *)state)->unk_AC = value_ac;
    ((S_8003AAE4_0 *)state)->unk_AE = value_ae;
}
