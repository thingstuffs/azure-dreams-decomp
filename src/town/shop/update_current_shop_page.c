#include "common.h"
#include "town/shop.h"

typedef struct S_800B0BD0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B0BD0_0;

typedef struct S_800B0BD0_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B0BD0_1;

/* Updates up to five entries on the current page and clears unused slots. */
void update_current_shop_page(void *list) {
    S_800B0BD0_0 *entry_list = list;
    s32 slot;

    for (slot = 0; slot < 5; slot++) {
        s32 entry_index = entry_list->unk_10 * 5 + slot;
        if (entry_index >= entry_list->unk_0C) {
            break;
        }
        set_shop_slot_colors(entry_list, entry_index);
    }

    for (; slot < 5; slot++) {
        *(s32 *)(((S_800B0BD0_1 *)(slot * 4 + entry_list->unk_CC))->unk_24) = 0;
    }
}
