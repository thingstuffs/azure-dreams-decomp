#include "common.h"
#include "m2c_compat.h"

typedef struct S_8051E904_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8051E904_1;   /* ((temp_s0 * 8) + arg0) in func_8051E904 */




extern s32 func_80017710(s32, M2C_UNK);
extern M2C_UNK func_80018A64();

typedef struct S_8051E904_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051E904_0;   /* arg1 in func_8051E904 */

s32 func_8051E904(s32 arg0, S_8051E904_0 *arg1, M2C_UNK arg2) {
    s32 temp_s0;

    temp_s0 = func_80017710(arg0, arg2);
    func_80018A64(arg1->unk_18);
    return ((S_8051E904_1 *)(((temp_s0 * 8) + arg0)))->unk_04;
}
