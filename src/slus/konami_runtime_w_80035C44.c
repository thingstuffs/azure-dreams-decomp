#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80035C44_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80035C44_0;   /* arg1 in func_80035C44 */

typedef struct S_80035C44_1 {
    u8 pad_00[0x68];
    M2C_UNK * unk_68;
} S_80035C44_1;   /* arg0 in func_80035C44 */


extern M2C_UNK func_80035C80;

void func_80035C44(S_80035C44_1 *arg0, S_80035C44_0 *arg1) {
    u16 temp_v0;

    temp_v0 = arg1->unk_02 + 0x10;
    arg1->unk_02 = temp_v0;
    if ((s16) temp_v0 >= 0x41) {
        arg1->unk_02 = 0x40U;
        arg0->unk_68 = &func_80035C80;
    }
}
