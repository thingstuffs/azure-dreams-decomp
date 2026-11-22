#include "common.h"
#include "frontend/card/slot_marker.h"
#include "shared/object_node.h"
#include "frontend/card.h"

/* Clear the update callback installed by the slot-window factory. */
void card_dev_clear_object_state(CardDevMenu10 *window) {
    NODE_HEADER(window)->update_callback = 0;
}
