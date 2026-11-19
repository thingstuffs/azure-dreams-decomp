#include "common.h"
#include "town/shop/display_element_layout_g00630.h"
#include "town/shop.h"

void build_display_entry_string(); /* Slot contract: loading images do not establish one callee contract. */                /* extern */

/* Run four setup routines with the supplied context and data. */
void initialize_display_entry(ActorRecord *actor, ItemMenuPart **data, SpritePartCommand *value) {
    layout_three_display_elements(actor, data, value);
    build_display_entry_string(actor, data);
    format_and_display_entity_stats(actor, data);
    populate_display_rows(actor, data);
}
