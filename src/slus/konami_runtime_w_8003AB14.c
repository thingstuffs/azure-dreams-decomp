#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_8003AB14_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_8003AB14_0;   /* arg0 in func_8003AB14 */

typedef struct S_8003AB14_1 {
    u8 pad_00[0x4];
    u16 unk_04;
    u16 unk_06;
    u16 unk_08;
    u16 unk_0A;
} S_8003AB14_1;   /* arg1 in func_8003AB14 */


void func_8003AB14(S_8003AB14_0 *arg0, S_8003AB14_1 *arg1) {
    arg0->unk_00 = (u16) arg1->unk_04;
    arg0->unk_02 = (u16) arg1->unk_06;
    arg0->unk_04 = (u16) arg1->unk_08;
    arg0->unk_06 = (u16) arg1->unk_0A;
}
