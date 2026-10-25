#include "common.h"
#include "dungeon/player/item.h"


/* Clear object fields and set its state to 0x2D when mode is zero, otherwise 0x2C. */
void begin_mode_selected_item_action(void *object_data, void *unused_1, void *unused_2, void *mode) {
    s8 *object = object_data;
    object[0x9A] = 0x2C;
    object[0x9B] = 0;
    *(s32 *)(object + 0x8C) = 0;
    if (mode == 0) {
        object[0x9A]++;
    }
}
