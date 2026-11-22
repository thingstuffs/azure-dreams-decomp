#include "frontend/libcard/card_chooser.h"
#include "shared/object_node.h"
#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/* Resume chooser input when its notice sets the completion flag. */
void card_sme_commit_pending_value(CardChooserBody *menu) {
    ObjectNodeHeader *node = NODE_HEADER(menu);
    u16 flags;

    flags = node->flags;
    if (flags & 0x2000) {
        node->flags = (u16) (flags & 0xDFFF);
        node->update_callback = menu->resume_input;
    }
}
