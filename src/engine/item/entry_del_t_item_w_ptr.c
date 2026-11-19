#include "common.h"
#include "town/shop/item_pointer_removal_g00615.h"
#include "shared/item_ids.h"

#include "engine/item.h"

extern u8 *town_item_list[];

/* Process type-0x13 entries whose indexed status is negative. */
void delete_negative_status_familiar_items(void)
{
    if (town_item_list[0] != 0) {
        u32 target_type = ITEM_KIND_FAMILIAR;
        u32 data_base = 0x80010000;
        u32 *entry_slot = (u32 *)(data_base + 0x29C);

        do {
            u8 *entry = (u8 *)*entry_slot;

            if (entry[1] == target_type) {
                s8 status = *(s8 *)(data_base + 0x333 +
                                    (entry[3] & 0x1F) * 84);

                if (status < 0) {
                    del_t_item_w_ptr(entry);
                    continue;
                }
            }
            entry_slot++;
        } while (*entry_slot != 0);
    }
}
