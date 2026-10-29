#include "sdk/libc.h"
#include "common.h"
#include "town/shop.h"
#include "town/shop/item.h"

extern u8 D_8008910C[];

/* Finds the first item with both key bytes within the player's home rank limit, or returns NULL. */
u8 *find_item_by_key_pair(s32 first_key, s32 second_key) {
    u8 last_indices[4];
    u8 *scan_base;
    s32 index;
    s32 last_index;

    memcpy(last_indices, D_8008910C, 4);
    last_index = last_indices[get_player_homerank()];
    scan_base = (u8 *) 0x80010000;
    for (index = 0; index <= last_index; index++) {
        if (scan_base[0x1F80 + index * 4] == first_key && scan_base[0x1F81 + index * 4] == second_key) {
            return (u8 *) 0x80011F80 + index * 4;
        }
    }
    return 0;
}
