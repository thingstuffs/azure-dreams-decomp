#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CCCCC_0 {
    u8 pad_00[0x68];
    u16 unk_68;
} S_800CCCCC_0;   /* arg0 in func_800CCCCC */

void func_800CCCCC(S_800CCCCC_0 *arg0) {
    arg0->unk_68 = (u16) (arg0->unk_68 + 1);
}
