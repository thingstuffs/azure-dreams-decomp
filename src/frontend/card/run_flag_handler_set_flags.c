#include "common.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/settings.h"

extern struct { s32 v; s32 pad[2]; } object_flag_block;

/* Run the flag handler and set entry and global flags when bit 0x2000 is set. */
void run_flag_handler_and_set_2000_flags(void *entry) {
    if (((ObjectNodeHeader *)entry - 1)->flags & 0x2000) {
        create_settings_controller();
        ((ObjectNodeHeader *)entry - 1)->flags = ((ObjectNodeHeader *)entry - 1)->flags | 0x8000;
        object_flag_block.v = object_flag_block.v | 0x8000;
    }
}
