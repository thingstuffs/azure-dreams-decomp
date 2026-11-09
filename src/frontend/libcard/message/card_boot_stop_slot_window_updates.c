#include "frontend/libcard/message_callbacks_api.h"
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard/message.h"



/* Stop this node by clearing its header update callback. */
void card_boot_stop_slot_window_updates(struct CardSlotWindow *window) {
    NODE_HEADER(window)->update_callback = 0;
}
