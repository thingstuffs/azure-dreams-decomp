#include "common.h"
#include "m2c_compat.h"

typedef struct S_806D45CC_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_806D45CC_2;   /* ((D_80016000->unk_08 * 8) + D_80016000->unk_40) in func_806D45CC */


typedef struct S_806D45CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D45CC_0;   /* arg0 in func_806D45CC */

typedef struct S_806D45CC_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_806D45CC_1;   /* D_80016000 in func_806D45CC */


M2C_UNK func_800176B8();             /* extern */
M2C_UNK func_80018594();                         /* extern */
extern S_806D45CC_1 *D_80016000;

void func_806D45CC(S_806D45CC_0 *arg0, M2C_UNK arg1) {
    func_80018594(arg0->unk_18);
    ((S_806D45CC_2 *)(((D_80016000->unk_08 * 8) + D_80016000->unk_40)))->unk_04 = 0;
    func_800176B8(arg0, arg1);
}
