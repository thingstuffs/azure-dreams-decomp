#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_800826B8;
extern M2C_UNK D_800CA114;
extern M2C_UNK D_800D6540;


void func_800CA6FC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D6540);
    D_800826B8 = 0;
    arg0->unk_54 = &D_800CA114;
}
