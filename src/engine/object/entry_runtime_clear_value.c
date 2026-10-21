#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/object.h"
#include "slus/data.h"

/* Calls runtime_clear_value for each of the 20 records starting at D_800816C0. */
void clear_twenty_runtime_records(void) {
    void *record;
    s32 record_index;

    record = runtime_object_pool;
    record_index = 0;
    do {
        runtime_clear_value(record);
        record_index += 1;
        record = (void *)((u8 *)record + 0x64);
    } while (record_index < 0x14);
}
