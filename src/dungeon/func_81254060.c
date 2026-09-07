#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800353F4();                   /* extern */
extern s32 D_80083170;
extern M2C_UNK D_80173FC8;

typedef struct S_81254060_0 {
    u8 pad_00[0x6D];
    s8 unk_6D;
} S_81254060_0;   /* arg3 in func_81254060 */

typedef struct S_81254060_1 {
    u8 pad_00[0x9B];
    s8 unk_9B;
} S_81254060_1;   /* arg0 in func_81254060 */

void func_81254060(S_81254060_1 *arg0, M2C_UNK arg1, M2C_UNK arg2, S_81254060_0 *arg3) {
    if (D_80083170 & 0x200000) {
        func_800353F4(&D_80173FC8);
        arg3->unk_6D = 0;
        arg0->unk_9B = 0;
    }
}
