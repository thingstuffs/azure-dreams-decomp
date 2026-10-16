/* Relink of matched dungeon/func_80977D88; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80173588_0 {
    u8 pad_00[0xA2];
    s16 unk_A2;
} S_80173588_0;   /* arg0 in func_80156358 */


s32 func_800AB538(S_80173588_0 *, void *, void *);
/* Call func_800AB538 and clear the state field at offset 0xA2. */
void func_80156358(S_80173588_0 *state, void *context, void *data) {
    func_800AB538(state, context, data);
    state->unk_A2 = 0;
}
