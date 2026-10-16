#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void runtimeClearValue();                   /* extern */
extern u8 D_800816C0[];

/* Calls runtimeClearValue for each of the 20 records starting at D_800816C0. */
void func_80033C8C(void) {
    void *record;
    s32 record_index;

    record = D_800816C0;
    record_index = 0;
    do {
        runtimeClearValue(record);
        record_index += 1;
        record = (void *)((u8 *)record + 0x64);
    } while (record_index < 0x14);
}
