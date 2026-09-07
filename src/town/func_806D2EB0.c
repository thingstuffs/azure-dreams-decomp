#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_800166B0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800166B0_1;   /* ((func_800161EC(arg0, arg2) * 8) + arg0) in func_800166B0 */

typedef struct S_800166B0_2 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_800166B0_2;   /* ((((S_800166B0_1 *)(((func_800161EC(arg0, arg2) * 8) + arg0)))->unk_02 * 4) + arg1->unk_14) in func_800166B0 */


#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_800161EC();
M2C_UNK func_80016D78();

typedef struct S_800166B0_0 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800166B0_0;   /* arg1 in func_800166B0 */

void func_800166B0(s32 arg0, S_800166B0_0 *arg1, M2C_UNK arg2) {
    func_80016D78(((S_800166B0_2 *)(((((S_800166B0_1 *)(((func_800161EC(arg0, arg2) * 8) + arg0)))->unk_02 * 4) + arg1->unk_14)))->unk_02);
}
