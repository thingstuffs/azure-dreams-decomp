#include "common.h"
#include "m2c_compat.h"

typedef struct S_81984AB0_1 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81984AB0_1;   /* arg0 in func_81984AB0 */

typedef struct S_81984AB0_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_81984AB0_2;   /* ((S_81984AB0_1 *)arg0)->unk_08 in func_81984AB0 */




typedef struct S_81984AB0_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
} S_81984AB0_0;   /* arg0 in func_81984AB0 */

void func_81984AB0(S_81984AB0_0 *arg0, s16 arg1) {
    s32 base;

    arg0->unk_04 = arg1;
    arg0->unk_05 = 0;
    base = ((S_81984AB0_2 *)(((S_81984AB0_1 *)arg0)->unk_08))->unk_0C;
    arg0->unk_14 = (u16) (arg0->unk_14 & 0x9FFF);
    arg0->unk_00 = (s32) (base + (arg1 * 0x16));
}
