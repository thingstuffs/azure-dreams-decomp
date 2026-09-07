#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017BF0_0 {
    u8 pad_00[0x40];
    void * unk_40;
} S_80017BF0_0;   /* D_80016000 in func_80017BF0 */

typedef struct S_80017BF0_1 {
    u8 pad_00[0xB0];
    s32 unk_B0;
} S_80017BF0_1;   /* ((S_80017BF0_0 *)D_80016000)->unk_40 in func_80017BF0 */




M2C_UNK func_80019814();                /* extern */
M2C_UNK func_8001A418();                     /* extern */
extern S_80017BF0_0 *D_80016000;


void func_80017BF0(s32 arg0, M2C_UNK arg1) {
    ((S_80017BF0_1 *)(D_80016000->unk_40))->unk_B0 = 0;
    func_8001A418(0x12CB);
    func_80019814(arg0, arg1);
}
