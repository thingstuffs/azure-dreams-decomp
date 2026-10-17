#include "common.h"
#include "m2c_compat.h"

void townSetShopSlotColors();                 /* extern */

typedef struct S_800B17E4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17E4_0;

/* Pass the object's data at offset 0x20 and its unk_08 value to townSetShopSlotColors. */
void townProcessShopObjectData(s32 object_addr) {
    S_800B17E4_0 *data;

    data = object_addr + 0x20;
    townSetShopSlotColors(data, data->unk_08);
}
