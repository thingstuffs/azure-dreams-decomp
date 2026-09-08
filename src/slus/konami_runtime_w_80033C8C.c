#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_80033C84();                   /* extern */
extern M2C_UNK D_800816C0;

/* Calls func_80033C84 for each of the 20 records starting at D_800816C0. */
void func_80033C8C(void) {
    void *record;
    s32 record_index;

    record = &D_800816C0;
    record_index = 0;
    do {
        func_80033C84(record);
        record_index += 1;
        record = (void *)((u8 *)record + 0x64);
    } while (record_index < 0x14);
}
