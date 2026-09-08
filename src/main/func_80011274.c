#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024274_0 {
    u8 pad_00[0x224];
    s32 unk_224;
    u8 pad_228[0x58];
    s32 * unk_280;
} S_80024274_0;   /* temp_v1 in func_80024274 */

/* Initialize the object's embedded state and clear its referenced word. */
void func_80024274(s32 object_addr) {
    S_80024274_0 *state;

    if (object_addr != 0) {
        state = object_addr + 0x20;
        state->unk_224 = 0x606868;
        *state->unk_280 = 0;
    }
}
