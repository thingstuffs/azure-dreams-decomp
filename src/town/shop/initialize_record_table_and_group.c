#include "common.h"
#include "m2c_compat.h"

s32 func_800B0718();                                /* extern */
struct TownB4C60; void get_zero_based_group_index(struct TownB4C60 *);                      /* extern */

typedef struct S_800B2B60_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x10];
    u32 unk_3C;
} S_800B2B60_0;   /* arg0 in initialize_record_table_and_group */

/* Initialize the record table pointer, stored value, and group index. */
void initialize_record_table_and_group(void *record) {
    ((S_800B2B60_0 *)record)->unk_3C = (u32 *)0x8001029C;
    ((S_800B2B60_0 *)record)->unk_28 = func_800B0718();
    get_zero_based_group_index(record + 0x1C);
}
