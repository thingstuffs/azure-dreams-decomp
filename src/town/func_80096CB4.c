#include "common.h"
#include "m2c_compat.h"

M2C_UNK SD_Call();                     /* extern */
M2C_UNK func_80094984(); /* extern */
M2C_UNK func_80094C1C();                  /* extern */
extern M2C_UNK D_800924EC;
extern M2C_UNK D_800D0110;

/* Reset and initialize the record, then assign its handler. */
void func_80094414(M2C_UNK **record, M2C_UNK unused, M2C_UNK setup_value) {
    SD_Call(0x50B);
    func_80094C1C(record);
    func_80094984(&D_800D0110, record, setup_value);
    *record = &D_800924EC;
}
