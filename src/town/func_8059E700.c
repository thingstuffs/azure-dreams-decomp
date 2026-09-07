#include "common.h"
#include "m2c_compat.h"

typedef struct S_8059E700_0 {
    u8 pad_00[0x38];
    void * unk_38;
} S_8059E700_0;   /* D_80016000 in func_8059E700 */

typedef struct S_8059E700_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_8059E700_1;   /* temp_v1 in func_8059E700 */


extern S_8059E700_0 *D_80016000;

void func_8059E700(s32 arg0) {
    S_8059E700_1 *temp_v1;

    temp_v1 = D_80016000->unk_38;
    temp_v1->unk_2D5C = (s32) (temp_v1->unk_2D5C - arg0);
}
