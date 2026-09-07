#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBAAC_0 {
    u8 pad_00[0x50];
    void (*unk_50)(void *, void *, M2C_UNK, M2C_UNK);
} S_800CBAAC_0;   /* arg0 in func_800CBAAC */





void func_800CBAAC(S_800CBAAC_0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    arg0->unk_50(arg0, arg0, arg1, arg2);
}
