#include "common.h"
#include "m2c_compat.h"

void *layout_three_display_elements(s32, void *, s32);                            /* extern */
void build_display_entry_string(); /* Slot contract: loading images do not establish one callee contract. */                /* extern */
void format_and_display_entity_stats(); /* Slot contract: loading images do not establish one callee contract. */                /* extern */
void populate_display_rows(); /* Slot contract: loading images do not establish one callee contract. */                /* extern */

/* Run four setup routines with the supplied context and data. */
void initialize_display_entry(s32 context, void * data, s32 value) {
    layout_three_display_elements(context, data, value);
    build_display_entry_string(context, data);
    format_and_display_entity_stats(context, data);
    populate_display_rows(context, data);
}
