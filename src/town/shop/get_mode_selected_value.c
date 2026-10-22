#include "common.h"
#include "town/shop.h"

extern s8 D_80089268[];

/* Return the selected value from the three global entries. */
u8 get_mode_selected_value(void) {
    s8 values[3];

    memcpy(values, D_80089268, 3);
    return values[get_player_homerank()];
}
