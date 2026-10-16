#include "common.h"
#include "m2c_compat.h"

void townPositionShopRowWidgets();                      /* extern */

typedef struct S_800B17C0_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17C0_0;   /* temp_a0 in townStoreShopEmbeddedValue */

/* Store a value in the embedded record and process the record. */
void townStoreShopEmbeddedValue(s32 base_addr, s32 value) {
    S_800B17C0_0 *record;

    record = base_addr + 0x20;
    record->unk_08 = value;
    townPositionShopRowWidgets(record);
}
