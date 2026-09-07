#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017824_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80017824_2;   /* (temp_a0 + arg0->unk_10) in func_80017824 */


s32 func_800169EC();                                /* extern */
M2C_UNK func_80017808();                      /* extern */
M2C_UNK func_8001A418();                     /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_80016A3C;
extern M2C_UNK D_8001B718;

typedef struct S_80017824_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017824_0;   /* arg0 in func_80017824 */

typedef struct S_80017824_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_80017824_1;   /* temp_a0_2 in func_80017824 */

s32 func_80017824(S_80017824_0 *arg0, s32 arg1) {
    s32 temp_a0;
    S_80017824_1 *temp_a0_2;

    if ((func_8001A510(0x479) == 0) && (func_800169EC() != 0)) {
        func_8001A418(0x479);
        temp_a0 = arg1 * 0x10;
        ((S_80017824_2 *)((temp_a0 + arg0->unk_10)))->unk_04 = &D_80016A3C;
        temp_a0_2 = temp_a0 + arg0->unk_10;
        temp_a0_2->unk_08 = &D_8001B718;
        func_80017808(temp_a0_2);
    }
    return 0;
}
