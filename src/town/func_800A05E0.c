#include "modules/town_town_windows.h"

/* Cleans up an object when its state check succeeds, or dispatches its callback and updates it. */
void cleanup_or_dispatch_object(void *object, s32 source, s32 context) {
    s8 *status_ptr;

    if (classify_record_by_state_and_position(object, source) != 0) {
        unlink_scene_list_node(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != NULL) {
            *status_ptr = 0;
        }
        func_80033D08(object);
        ((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 = (u16) (((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(object, object, source, context);
    if (!(((func_800A05E0_S_8009DD40_0_pre *)object)[-1].unk_00 & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(source), object);
        if (((Rec_D_80082D58 *)object)->unk_4D == 0x13) {
            func_800478B8(context);
        }
    }
}
