#include "common.h"
#include "m2c_compat.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "town/shop/position.h"


/*
 * Writes X/Y offsets (-95, 48) and (97, 48) into the linked elements reached through child fields
 * 0x74 and 0x78.
 */
void position_shop_child_elements(ShopWindow *window) {
    window->widgets->left_child->data->x = -0x5F;
    window->widgets->left_child->data->y = 0x30;
    window->widgets->right_child->data->x = 0x61;
    window->widgets->right_child->data->y = 0x30;
}
