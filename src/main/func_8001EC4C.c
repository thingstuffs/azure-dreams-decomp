#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003D548();                     /* extern */
M2C_UNK func_80400EF8();                            /* extern */
extern s32 D_80010208;
extern s16 D_80011F48;
extern s8 D_8008CA34;

typedef struct S_8001EC4C_0 {
    u8 pad_00[0x44];
    s32 unk_44;
} S_8001EC4C_0;   /* arg0 in func_8001EC4C */

void func_8001EC4C(S_8001EC4C_0 *arg0) {
    M2C_UNK var_a0;
    s16 var_v1;

    D_8008CA34 = 2;
    func_80400EF8();
    var_v1 = 1;
    if (arg0->unk_44 == 0) {
        var_v1 = 3;
    }
    D_80011F48 = var_v1;
    var_a0 = 4;
    if (D_80010208 != 0) {
        var_a0 = 5;
    }
    func_8003D548(var_a0);
}
