#include "town/scene/entry_requests.h"
#include "town/shop/object/lshop_g00008.h"
#include "town/scene.h"

/* The placed slot helper consumes only a0; the other registers are unused. */
void release_lshop_entry_and_compact(s32 slot_index) {
    release_lshop_entry(slot_index);
    compact_lshop_entry_list();
}
