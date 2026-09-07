#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660;
extern M2C_UNK D_800C5ADC;
extern M2C_UNK D_800D54BC;


void func_800C5944(Rec_func_80094268_arg0 *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    func_800C2E84(arg0, arg2, &D_800D54BC);
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    arg0->unk_54 = &D_800C5ADC;
}
