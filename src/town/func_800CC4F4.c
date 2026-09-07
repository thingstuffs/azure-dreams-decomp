#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C9864;
extern M2C_UNK D_800D64DC;


void func_800C9C54(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D64DC);
    arg0->unk_50.as_pm = &D_800C9864;
}
