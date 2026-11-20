#include "shared/object_node.h"
#include "town/shop.h"

/* close_twin_shop: Schedule the shop cleanup callback if the shop exists. */
void close_twin_shop(ObjectNodeHeader *shop) {
    if (shop) {
        shop->update_callback = close_shop;
    }
}
