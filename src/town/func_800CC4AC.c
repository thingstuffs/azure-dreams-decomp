#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C97F4;
extern M2C_UNK D_800D64C8;


void func_800C9C0C(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D64C8);
    arg0->unk_50.as_pm = &D_800C97F4;
    arg0->unk_6C.as_s16 = 0x15;
}
