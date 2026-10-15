/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"

s32 SD_Call();                     
void func_80094984(); 
void func_80094C1C();                  
extern s32 D_80093250;
extern s32 D_800D00B8;

void func_80094714(s32 **record, s32 unused, s32 setup_value) {
    SD_Call(0x512);
    func_80094C1C(record);
    func_80094984(&D_800D00B8, record, setup_value);
    *record = &D_80093250;
}
