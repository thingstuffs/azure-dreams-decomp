#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027018_arg0.h"

extern M2C_UNK D_80077EF0;
extern M2C_UNK D_80077EFC;


void func_80027018(void *arg0) {
    *((Rec_func_80027018_arg0 *)arg0)->unk_F0.as_ppm = &D_80077EF0;
    *((Rec_func_80027018_arg0 *)arg0)->unk_F4.as_ppm = &D_80077EFC;
    *((Rec_func_80027018_arg0 *)arg0)->unk_F8.as_ppv = arg0 + 4;
    *((Rec_func_80027018_arg0 *)arg0)->unk_FC.as_ppv = arg0 + 0x7C;
}
