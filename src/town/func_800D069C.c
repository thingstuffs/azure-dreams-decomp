#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800CD70C;
extern M2C_UNK D_800D72AC;


void func_800CDDFC(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D72AC);
    arg0->unk_50.as_pm = &D_800CD70C;
    arg0->unk_84.as_s16 = 0x50;
    arg0->unk_6C.as_s16 = 0xD2;
}
