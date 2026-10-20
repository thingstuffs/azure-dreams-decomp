#include "town/menu/window.h"

/* Reset the object handler and restore its saved byte unless the check returns two. */
void reset_object_handler_and_saved_byte(void *object, void *context) {
    if (classify_record_by_state_and_position(object, context) != 2) {
        register_node_if_unregistered(object, project_sprite_chain);
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_00 = &dispatch_object_or_switch_alternate_state;
        ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_25 = (u8) ((func_800A0824_S_8009DF84_0 *)((u8 *)object - 0x10))->unk_BC;
    }
}
