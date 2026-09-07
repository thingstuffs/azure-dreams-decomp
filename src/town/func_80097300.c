#include "common.h"



typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80094A38();

typedef struct S_80094A60_0 {
    u8 pad_00[0x16];
    s16 unk_16;
} S_80094A60_0;   /* arg1 in func_80094A60 */

void func_80094A60(s32 *arg0, S_80094A60_0 *arg1) {
    s32 value = arg0[arg1->unk_16];
    if (value != 0) {
        func_80094A38(value);
    }
}
