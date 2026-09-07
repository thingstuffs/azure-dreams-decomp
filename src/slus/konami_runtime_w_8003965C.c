#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003965C_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8003965C_0;   /* arg0 in func_8003965C */

typedef struct S_8003965C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_8003965C_1;   /* temp_a2 in func_8003965C */


void func_8003965C(S_8003965C_0 *arg0) {
    S_8003965C_1 *temp_a2;

    temp_a2 = arg0->unk_1C;
    arg0->unk_1C = (void *) (temp_a2->unk_00 + (temp_a2->unk_01 << 8) + (temp_a2->unk_02 << 0x10) + (temp_a2->unk_03 << 0x18));
}
