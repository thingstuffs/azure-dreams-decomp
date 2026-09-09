#include "common.h"

#include "common.h"

extern u8 *D_8001029C[];
extern s8 D_80010333[];
extern void del_t_item_w_ptr(u8 *entry);

/* Process type-0x13 entries whose indexed status is negative. */
void func_8003B820(void)
{
    if (D_8001029C[0] != 0) {
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
