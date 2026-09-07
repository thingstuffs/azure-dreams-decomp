#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D9E4_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_8009D9E4_0;   /* arg0 in func_8009D9E4 */

typedef struct S_8009D9E4_1 {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_8009D9E4_1;   /* arg1 in func_8009D9E4 */

void func_8009D9E4(S_8009D9E4_0 *arg0, S_8009D9E4_1 *arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;
    s16 temp_v0_4;

    temp_v0 = arg0->unk_00 + arg0->unk_04;
    arg1->unk_08 = temp_v0;
    arg1->unk_00 = temp_v0;
    temp_v0_2 = arg0->unk_08 + (arg0->unk_00 + arg0->unk_04);
    arg1->unk_0C = temp_v0_2;
    arg1->unk_04 = temp_v0_2;
    temp_v0_3 = arg0->unk_02 + arg0->unk_06;
    arg1->unk_06 = temp_v0_3;
    arg1->unk_02 = temp_v0_3;
    temp_v0_4 = arg0->unk_0A + (arg0->unk_02 + arg0->unk_06);
    arg1->unk_0E = temp_v0_4;
    arg1->unk_0A = temp_v0_4;
}
