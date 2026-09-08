#include "common.h"
#include "m2c_compat.h"

extern s32 D_80174CE0;

typedef struct S_80170CBC_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80170CBC_0;   /* temp_v1 in func_80170CBC */

/* Clear the object's halfword field and increment its byte counter. */
void func_80170CBC(void) {
    S_80170CBC_0 *object;

    object = D_80174CE0 + 0x20;
    object->unk_96 = 0;
    object->unk_9A = (u8) (object->unk_9A + 1);
}
