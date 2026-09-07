#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80098988();                            /* extern */
extern u8 D_80082660;

typedef struct S_8009A58C_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_8009A58C_0;   /* arg0 in func_8009A58C */

void func_8009A58C(S_8009A58C_0 *arg0) {
    *((arg0->unk_40 * 8) + &D_80082660) = 0;
    func_80098988();
}
