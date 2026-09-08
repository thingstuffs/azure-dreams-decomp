#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A782C_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in func_800A782C, addressed as arg0[-1] */

typedef struct S_800A782C_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800A782C_1;   /* arg1 in func_800A782C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033CD8();
M2C_UNK func_800A790C();
M2C_UNK func_800C2CB0();
extern M2C_UNK D_80045340;
extern M2C_UNK D_800A78AC;
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void func_800A782C(void *object, S_800A782C_1 *state, M2C_UNK context) {
    ((S_800A782C_0_pre *)object)[-1].unk_00 = &D_800A78AC;
    func_800C2CB0(object, context, &D_800F842C, 0);
    func_80033CD8(object, &D_80045340);
    state->unk_0A = 0;
    func_800A790C(object, state, context);
}
