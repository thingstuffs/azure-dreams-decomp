#include "common.h"
#include "frontend/card.h"
#include "frontend/settings.h"

extern struct { s32 v; s32 pad[2]; } object_flag_block;

/* Run the flag handler and set entry and global flags when bit 0x2000 is set. */
void run_flag_handler_and_set_2000_flags(void *entry) {
    if (*(u16 *)((s8 *)entry - 2) & 0x2000) {
        create_settings_controller();
        *(u16 *)((s8 *)entry - 2) = *(u16 *)((s8 *)entry - 2) | 0x8000;
        object_flag_block.v = object_flag_block.v | 0x8000;
    }
}
