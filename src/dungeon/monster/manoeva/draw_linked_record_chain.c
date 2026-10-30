#include "common.h"

extern void project_sprite_commands(void *context, s32 position, void *entry, s32 depth_bias); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */

/* Clears the scratchpad counter and processes each record in the linked chain. */
s32 draw_linked_record_chain(u8 *record_data, s32 record_value, u8 *linked_data) {
    *(s32 *)0x1F80013C = 0;
    for (;;) {
        project_sprite_commands(record_data, record_value, linked_data, -0x10);
        linked_data = *(u8 **)(record_data - 8);
        if (linked_data == 0) {
            return 0;
        }
        record_data = linked_data + 0x20;
        record_value = *(s32 *)(linked_data + 8);
        linked_data = *(u8 **)(linked_data + 0xC);
    }
}

/* MECHANISM: The true-space j to 0x80175D90 is a local loop backedge, not an external tail call.
   Natural loop liveness holds arg0 in s0, yielding the 24-byte frame and exact save order.
   Testing arg2 before its source-level advance lets gcc place that advance in the branch delay slot. */
