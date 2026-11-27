#include "town/menu.h"
#include "common.h"
#include "town/map/variant_data.h"
#include "town/shop.h"
#include "town/shop/target_position_data.h"

/* Selects a town entry and writes its root-relative coordinates to the output. */
s32 set_shop_target_to_entry(s32 entryIndex) {
    TownRectangle *root = town_script_state_slots[0];
    TownSpawnEntry *entry;
    TownSpawnEntry *entries;
    ShopTargetPosition *output;
    u32 rootX;
    u16 rootY;
    u32 entryX;
    u16 entryY;
    /* BYTES: indexed pointer arithmetic reverses the operands of the address add. */
    unsigned long entry_offset;
    s32 selectedEntryIndex = entryIndex;

    shop_target_entry_index = selectedEntryIndex;
    entry_offset = selectedEntryIndex * sizeof(*entry);
    entries = root->entry_list[1];
    rootX = root->origin_x;
    rootY = root->origin_y;
    shop_target_position.x.v = 0;
    entry = (TownSpawnEntry *)(entry_offset + (unsigned long)entries);
    entryX = entry->x_offset;
    output = &shop_target_position;
    output->y.v = 0;
    entryX += rootX;
    output->x.w.i = entryX;
    entryY = entry->y_offset;
    output->y.w.i = entryY + rootY;
    output->z.v = -0x200000;
    return selectedEntryIndex;
}
