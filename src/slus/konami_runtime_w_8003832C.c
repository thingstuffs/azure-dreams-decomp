#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003832C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_8003832C_0;   /* arg0 in func_8003832C */


M2C_UNK func_80039AF0();                            /* extern */
extern M2C_UNK func_80038368;

/* Initialize the context and set its next handler and state. */
void func_8003832C(S_8003832C_0 *context) {
    func_80039AF0();
    context->unk_18 = 5;
    context->unk_10 = &func_80038368;
}
