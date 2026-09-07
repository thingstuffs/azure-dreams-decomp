#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

extern u8 D_80082660;
extern M2C_UNK D_800C3BF4;


void func_800C58F4(Rec_func_80094268_arg0 *arg0) {
    *((arg0->unk_60 * 8) + &D_80082660) = 0;
    arg0->unk_54 = &D_800C3BF4;
}
