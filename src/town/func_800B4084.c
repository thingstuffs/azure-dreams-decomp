#include "common.h"
#include "m2c_compat.h"

void set_shop_slot_colors();                 /* extern */

typedef struct S_800B17E4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800B17E4_0;

/* Pass the object's data at offset 0x20 and its unk_08 value to set_shop_slot_colors. */
void process_shop_object_data(s32 object_addr) {
    S_800B17E4_0 *data;

    data = object_addr + 0x20;
    set_shop_slot_colors(data, data->unk_08);
}
