#include "town/menu/window.h"

/* Dispatches an object callback or switches the object to its alternate state. */
void dispatch_object_or_switch_alternate_state(func_800A075C_S_func_8009DEBC_0 *object, s32 source, s32 context) {
    u8 saved_state;

    if (classify_record_by_state_and_position(object, source) == 2) {
        unlink_node_if_registered(object);
        saved_state = object->unk_15;
        object->unk_15 = 0;
        ((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_00 = reset_object_handler_and_saved_byte;
        object->unk_AC = saved_state;
        return;
    }

    object->unk_50(object, object, source, context);
    if (!(((func_800A075C_S_func_8009DEBC_1 *)((u8 *)object - 0x10))->unk_0E & 0x8000)) {
        set_state_bytes_from_flags(update_state_when_active(source), object);
        if (object->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
