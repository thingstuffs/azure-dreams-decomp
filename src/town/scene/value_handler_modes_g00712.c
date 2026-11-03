/* Dispatch value handler modes (G00712). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8032EA2C. */
#include "town/scene/value_handler_modes_g00712.h"
#include "town/scene.h"
#include "town/shop/state.h"

/* Calls func_80018FDC with the supplied value and a zero second argument. */
void call_value_handler_mode_0(void *entries) {
    process_lshop_entries(entries, 0);
}

/* Forwards the index plus four to func_80018FDC with mode 1. */
void call_value_handler_index_plus_4(u8 *entries) {
    process_lshop_entries(entries + 4, 1);
}
