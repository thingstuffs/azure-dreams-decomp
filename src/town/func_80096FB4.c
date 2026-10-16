/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

s32 SD_Call();                     
void townCallTheHandlerSelectsNonzeroEntry(); 
void townStoreTheValidSharedAngleInOffsetHex10();                  
extern s32 D_80093250;
extern s32 D_800D00B8;

void func_80094714(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x512);
    townStoreTheValidSharedAngleInOffsetHex10(record);
    townCallTheHandlerSelectsNonzeroEntry(&D_800D00B8, record, setup_value);
    *record = &D_80093250;
}
