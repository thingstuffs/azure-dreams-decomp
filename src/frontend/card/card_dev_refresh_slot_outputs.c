#include "shared/object_node.h"
#include "frontend/card/choice_panel.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/* Refresh the choice panel stored after its node header. */
void card_dev_refresh_slot_outputs(ObjectNodeHeader *node, s32 *enabled, s32 *selected) {
    card_boot_update_slot_outputs(NODE_BODY(node), enabled, selected);
}
