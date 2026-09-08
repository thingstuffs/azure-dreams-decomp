#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_80036210_arg0.h"


typedef struct S_80036210_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80036210_2;   /* ((Rec_func_80036210_arg0 *)arg0)->unk_74.as_pv in func_80036210 */




M2C_UNK func_80036B10(); /* extern */
extern M2C_UNK D_80081FDC;
extern M2C_UNK D_80082414;
extern M2C_UNK func_8003626C;

void func_80036210(Rec_func_80036210_arg0 *arg0) {
    func_80036B10(&D_80082414, &D_80081FDC, arg0, 0, ((S_80036210_2 *)(((Rec_func_80036210_arg0 *)arg0)->unk_74.as_pv))->unk_80);
    arg0->unk_4C = 0;
    arg0->unk_68 = &func_8003626C;
}
