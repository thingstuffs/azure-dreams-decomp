#include "common.h"
#include "town/menu.h"
#include "town/data.h"

/* Store D_80126A60 at the location pointed to by D_8012974C. */
void store_cached_value_at_pointer(void) {
    *selected_menu_value_target = selected_menu_value;
}
