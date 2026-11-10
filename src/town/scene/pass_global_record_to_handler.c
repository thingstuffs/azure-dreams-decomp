#include "town/shop/object/lshop_g00008.h"
#include "common.h"
#include "town/scene.h"
#include "town/shop/object.h"

extern Copy4 D_8001BE60;
/* Passes the address of D_8001BE60 to append_shop_entry. */
void pass_global_record_to_handler(void) {
    append_town_item(&D_8001BE60);
}
