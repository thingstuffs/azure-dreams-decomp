#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
M2C_UNK func_800C2E84();                /* extern */
extern M2C_UNK D_800C34EC;


void func_800C37C4(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, *arg0->unk_7C.as_ps32);
    arg0->unk_50.as_pm = &D_800C34EC;
    arg0->unk_6C.as_s16 = (s16) (((func_800374F4(4) & 0xFFFF) * 0x15) + 0x15);
}
