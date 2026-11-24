#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/shop.h"
#include "town/scene/active_object_records_g00710.h"

/* Build the goods entries, open the shop and return its handle. */
TownShopHandle *open_shop_with_goods_entries(void) {
    clear_bytes((s8 *)shop_scene_entry_bytes, 0x100);
    build_shop_goods_entries(shop_scene_entry_bytes);
    /* The service returns the handle as an int. */
    return shop_scene_registration_handle = (TownShopHandle *)(unsigned long)
        town_scene_root->services->callback_068(0, 0, 1, shop_scene_entry_bytes);
}
