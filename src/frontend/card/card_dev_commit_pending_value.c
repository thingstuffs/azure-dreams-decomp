#include "frontend/card/save_operation.h"
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"



/* Copy the saved callback to this node's update slot when flag 0x2000 is set. */
void card_dev_commit_pending_value(void *record_data) {
    u16 flags;

    flags = ((ObjectNodeHeader *)record_data - 1)->flags;
    if (flags & 0x2000) {
        ((ObjectNodeHeader *)record_data - 1)->flags = (u16) (flags & 0xDFFF);
        ((ObjectNodeHeader *)record_data - 1)->update_callback = ((CardSaveOperationBody *)record_data)->completion_callback;
    }
}
