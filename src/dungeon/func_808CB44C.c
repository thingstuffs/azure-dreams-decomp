#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80129728[16];
extern s32 D_801331A0;

/* Restore 12 referenced values from the backup array. */
void func_801238E4(void) {
    M2C_UNK *table_base;
    s32 **value_slot;
    s32 *value_ptr;
    s32 *backup_value;
    s32 value_index;

    value_index = 0x10;
    backup_value = &D_801331A0;
    table_base = D_80129728;
    value_slot = (s32 **)(table_base + 0x10);
    do {
        value_ptr = *value_slot;
        value_slot++;
        value_index++;
        *value_ptr = *backup_value;
        backup_value++;
    } while (value_index < 0x1C);
}
