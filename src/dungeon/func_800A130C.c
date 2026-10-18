#include "common.h"
#include "m2c_compat.h"

void clear_selected_item_flag_400();                        /* extern */

/* Sends the two-byte command 1, 0x12. */
void clear_item_flag_400_for_egg_one(void) {
    s8 command[2];

    command[0] = 1;
    command[1] = 0x12;
    clear_selected_item_flag_400((s8 *)&command[0]);
}
