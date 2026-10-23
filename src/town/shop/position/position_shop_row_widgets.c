#include "town/shop/shop_window_layout_g00610.h"

void position_shop_row_widgets(ShopWindow *menu) {
    ShopWindowWidgets *widgets;

    menu->widgets->cursor->data->x = -0x58;
    menu->widgets->cursor->data->y.s = (s16)(((menu->selected_entry % 5) * 0x10) + 8);
    menu->widgets->unk_0C->data->x = 0;
    widgets = menu->widgets;
    widgets->unk_0C->data->y.s = (s16)(widgets->cursor->data->y.u - 9);
}
