#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800395F0_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
    u8 pad_20[0x5C];
    s32 * unk_7C;
} S_800395F0_0;   /* arg0 in func_800395F0 */

typedef struct S_800395F0_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800395F0_1;   /* temp_a2 in func_800395F0 */


void func_800395F0(S_800395F0_0 *arg0) {
    S_800395F0_1 *temp_a2;

    *arg0->unk_7C = arg0->unk_1C + 4;
    temp_a2 = arg0->unk_1C;
    arg0->unk_7C = (s32 *) (arg0->unk_7C + 1);
    arg0->unk_1C = (void *) (temp_a2->unk_00 + (temp_a2->unk_01 << 8) + (temp_a2->unk_02 << 0x10) + (temp_a2->unk_03 << 0x18));
}
