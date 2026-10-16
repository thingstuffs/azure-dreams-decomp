#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80099B00;

typedef struct S_8009A18C_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_8009A18C_0;   /* arg0 in townInitializePlayerDataReference */

typedef struct S_8009A18C_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009A18C_1;   /* arg1 in townInitializePlayerDataReference */

/* Initializes the data reference and state value. */
void townInitializePlayerDataReference(S_8009A18C_0 *data_ref, S_8009A18C_1 *state) {
    data_ref->unk_04 = &D_80099B00;
    state->unk_14 = 0xFFF60000;
}
