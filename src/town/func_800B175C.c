#include "common.h"
#include "m2c_compat.h"

void dispatch_item_menu_data_update();                      /* extern */

typedef struct S_800AEEBC_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x8];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
} S_800AEEBC_0;   /* arg0 in initialize_item_menu_record_fields */

/* Set four record values and initialize its trailing data. */
void initialize_item_menu_record_fields(void *record, s32 value_3c, s32 value_34, s32 value_28, s32 value_38) {
    ((S_800AEEBC_0 *)record)->unk_3C = value_3c;
    ((S_800AEEBC_0 *)record)->unk_34 = value_34;
    ((S_800AEEBC_0 *)record)->unk_28 = value_28;
    ((S_800AEEBC_0 *)record)->unk_38 = value_38;
    dispatch_item_menu_data_update(record + 0x40);
}
