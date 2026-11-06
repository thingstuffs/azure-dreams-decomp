#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/data.h"

/* Existing-identity bank: words 0..84 are byte-proven data, not C code. */

/* Store D_80126A60 at the destination pointed to by D_8012974C. */
void store_cached_value_at_pointer(void) {
    *selected_menu_value_target = selected_menu_value;
}
