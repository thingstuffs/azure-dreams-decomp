#include "common.h"
#include "m2c_compat.h"
#include "town/shop.h"

struct Rec_func_800B2DA0_arg1; void update_paged_menu_record(struct Rec_func_800B2DA0_arg1 *);                         /* extern */

/* Passes the base plus 0x20 to update_paged_menu_record. */
void update_and_finalize_record_node(s32 base) {
    update_paged_menu_record((struct Rec_func_800B2DA0_arg1 *)(base + 0x20));
}
