#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"
#include "frontend/card.h"
#include "frontend/settings.h"

/* Run the flag handler and set entry and global flags when bit 0x2000 is set. */
void create_settings_controller_and_flag_removal(void *entry_arg) {
    ObjectNodeHeader *entry = entry_arg;

    if ((entry - 1)->flags & 0x2000) {
        create_settings_controller();
        (entry - 1)->flags = (entry - 1)->flags | 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
