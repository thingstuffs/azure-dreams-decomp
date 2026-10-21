#include "common.h"

#include "common.h"
#include "engine/item.h"

extern u8 *town_item_list[];
extern void del_t_item_w_ptr(u8 *entry);

/* Process type-0x13 entries whose indexed status is negative. */
void remove_monster_items_with_negative_status(void)
{
    if (town_item_list[0] != 0) {
        u32 target_type = 0x13;
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
