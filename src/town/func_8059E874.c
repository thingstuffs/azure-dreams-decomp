#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016874_0 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_80016874_0;   /* D_80016000 in func_80016874 */

typedef struct S_80016874_1 {
    u8 pad_00[0x7];
    u8 unk_07;
} S_80016874_1;   /* temp_v1 in func_80016874 */


extern S_80016874_0 *D_80016000;

void func_80016874(void) {
    S_80016874_1 *temp_v1;

    temp_v1 = D_80016000->unk_40 + 0x68;
    temp_v1->unk_07 = (u8) (temp_v1->unk_07 + 1);
}
