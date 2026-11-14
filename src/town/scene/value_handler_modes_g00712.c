/* Dispatch value handler modes. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8032EA2C. */
#include "town/scene/value_handler_modes_g00712.h"
#include "town/scene.h"
#include "town/shop/state.h"

/* Calls func_80018FDC with the supplied value and a zero second argument. */
void process_lshop_entries_default(void *entries) {
    apply_shop_transaction(entries, 0);
}

/* Forwards the index plus four to func_80018FDC with mode 1. */
void process_lshop_entries_after_header(u8 *entries) {
    apply_shop_transaction(entries + 4, 1);
}
