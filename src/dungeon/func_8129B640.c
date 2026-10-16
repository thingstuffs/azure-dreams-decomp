/* Relink of matched dungeon/func_80977D88 at file 0x997D88; imports and data use paired retail relocations. */
#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in func_80153E40 */


s32 func_800AA1F0(S_80173588_0 *, void *, void *);
/* Call func_800AA1F0 and clear the state field at offset 0xA2. */
void func_80153E40(S_80173588_0 *state, void *context, void *data) {
    func_800AA1F0(state, context, data);
    state->unk_A2 = 0;
}
