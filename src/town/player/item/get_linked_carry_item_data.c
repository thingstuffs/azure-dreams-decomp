#include "town/player/carry_item.h"

/* Return the linked record data when its type or data tag qualifies, or zero. */
void *get_linked_carry_item_data(void *record, s32 unused_first, s32 unused_second) {
    u8 *linked_record = *(u8 **)((u8 *)record + 0x2C);

    if (linked_record != 0) {
        s32 type = 4;

        if ((linked_record[0x14] == type) || (linked_record[0x4D] == 0xD)) {
            return linked_record + 0x4C;
        }
    }
    return 0;
}
