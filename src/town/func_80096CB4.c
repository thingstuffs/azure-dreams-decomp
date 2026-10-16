#include "common.h"
#include "m2c_compat.h"

M2C_UNK SD_Call();                     /* extern */
void townCallTheHandlerSelectsNonzeroEntry(); /* extern */
void townStoreTheValidSharedAngleInOffsetHex10();                  /* extern */
extern M2C_UNK D_800924EC;
extern M2C_UNK D_800D0110;

/* Reset and initialize the record, then assign its handler. */
void func_80094414(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x50B);
    townStoreTheValidSharedAngleInOffsetHex10(record);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D0110, record, setup_value);
    *record = &D_800924EC;
}
