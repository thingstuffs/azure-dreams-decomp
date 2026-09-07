#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80033D08();                            /* extern */
extern M2C_UNK D_8009F2A8;

typedef struct S_8009F48C_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
} S_8009F48C_0;   /* arg0 in func_8009F48C */

void func_8009F48C(S_8009F48C_0 *arg0) {
    func_80033D08();
    arg0->unk_50 = &D_8009F2A8;
}
