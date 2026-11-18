#include "town/shop.h"
#include "town/shop/storage_menu.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B4978_1 {
    u8 pad_00[0x40];
    s32 unk_40;
} S_800B4978_1;

/* Passes the source data and its parameter to the destination component. */
void forward_source_data_to_component(StorageOwner *object) {
    void *source_data;

    source_data = object->owner;
    fill_ten_paged_output_slots((s32 **)&object->parts[6], source_data + 0x2C, ((S_800B4978_1 *)source_data)->unk_40);
}
