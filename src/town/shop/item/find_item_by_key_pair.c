#include "sdk/libc.h"
#include "shared/game_state.h"
#include "common.h"
#include "town/shop.h"
#include "town/shop/item.h"

extern u8 D_8008910C[];

/* Finds the first item with both key bytes within the player's home rank limit, or returns NULL. */
u8 *find_item_by_key_pair(s32 first_key, s32 second_key) {
    u8 last_indices[4];
    s32 index;
    s32 last_index;

    memcpy(last_indices, D_8008910C, 4);
    last_index = last_indices[get_player_homerank()];
    for (index = 0; index <= last_index; index++) {
        if (GAME_STATE->unk_1F80[index].unk_00 == first_key && GAME_STATE->unk_1F80[index].kind == second_key) {
            return (u8 *)&GAME_STATE->unk_1F80[index];
        }
    }
    return 0;
}
