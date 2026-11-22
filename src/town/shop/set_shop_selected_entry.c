#include "common.h"
#include "town/shop/shop_window_layout_g00610.h"
#include "m2c_compat.h"
#include "town/shop.h"
#include "slus.h"



/* Store a value in the embedded record and process the record. */
void set_shop_selected_entry(ObjectNodeHeader *node, s32 value) {
    ShopWindow *record;

    record = NODE_BODY(node);
    record->selected_entry = value;
    position_shop_row_widgets(record);
}
