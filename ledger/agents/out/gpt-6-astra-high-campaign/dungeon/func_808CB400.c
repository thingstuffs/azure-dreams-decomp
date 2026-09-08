#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK()  (0)

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80129728[];
extern s32 D_801331A0;

/* Save 12 referenced values to the backup array and clear the originals. */
void func_80123898(void) {
    u8 *table_base;
    u8 *value_slot;
    s32 *value_ptr;
    s32 *backup_value;
    s32 value_index;

    value_index = 0x10;
    backup_value = &D_801331A0;
    table_base = D_80129728;
    value_slot = table_base + 0x40;
    do {
        value_index += 1;
        *backup_value = **(s32 **)value_slot;
        value_ptr = *(s32 **)value_slot;
        value_slot += 4;
        *value_ptr = 0;
        backup_value += 1;
    } while (value_index < 0x1C);
}
