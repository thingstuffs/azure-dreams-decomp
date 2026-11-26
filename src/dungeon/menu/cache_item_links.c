#include "engine/texture.h"
#include "dungeon/menu_cache.h"

/* The last value marks the end of the chain order. */
const u8 cached_item_part_order[41] __attribute__((aligned(1))) = {
    2, 3, 0, 1, 38, 39, 5,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    4, 40,
};

/* Link the 40 item display parts in draw order. */
ItemMenuPart *link_item_display_entries(ItemMenuPart **entries)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)entries, cached_item_part_order, 40);
}
