#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016DE0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016DE0_0;   /* D_80016000 in func_80016DE0 */

typedef struct S_80016DE0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016DE0_1;   /* temp_v1 in func_80016DE0 */


extern S_80016DE0_0 *D_80016000;

void func_80016DE0(void) {
    S_80016DE0_1 *temp_v1;

    temp_v1 = D_80016000->unk_1C;
    temp_v1->unk_04 = (s32) ((temp_v1->unk_04 << 6) + 0x220);
}
