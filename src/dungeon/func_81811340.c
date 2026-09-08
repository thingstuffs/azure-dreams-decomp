#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025888();                /* extern */

typedef struct S_80026340_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x48];
    s32 unk_54;
} S_80026340_0;   /* temp_a0 in func_80026340 */

/* Set the embedded state field to 4 and apply it to the linked object. */
void func_80026340(s32 object_addr) {
    S_80026340_0 *state;

    state = object_addr + 0x20;
    state->unk_08 = 4;
    func_80025888(state->unk_54, 4);
}
