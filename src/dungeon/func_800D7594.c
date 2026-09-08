#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800E2804;
extern M2C_UNK D_800E2828;
extern M2C_UNK D_800E28B8;

typedef struct S_800DCCF4_0 {
    s32 unk_00;
    M2C_UNK * unk_04;
    M2C_UNK * unk_08;
    M2C_UNK * unk_0C;
} S_800DCCF4_0;   /* arg0 in func_800DCCF4 */


M2C_UNK func_800DCC3C(S_800DCCF4_0 *);
s32 func_800DCCF4(S_800DCCF4_0 *arg0, s32 arg1) {
    arg0->unk_04 = &D_800E2828;
    arg0->unk_08 = &D_800E28B8;
    arg0->unk_00 = arg1;
    arg0->unk_0C = &D_800E2804;
    func_800DCC3C(arg0);
    return 1;
}
