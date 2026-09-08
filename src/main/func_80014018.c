#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027018_arg0.h"

extern M2C_UNK D_80077EF0;
extern M2C_UNK D_80077EFC;


/* Populate output pointers with shared data and embedded record addresses. */
void func_80027018(void *record) {
    *((Rec_func_80027018_arg0 *)record)->unk_F0.as_ppm = &D_80077EF0;
    *((Rec_func_80027018_arg0 *)record)->unk_F4.as_ppm = &D_80077EFC;
    *((Rec_func_80027018_arg0 *)record)->unk_F8.as_ppv = record + 4;
    *((Rec_func_80027018_arg0 *)record)->unk_FC.as_ppv = record + 0x7C;
}
