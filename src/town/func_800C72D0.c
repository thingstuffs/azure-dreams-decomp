#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_80033D08();                      /* extern */
void unlink_scene_list_node();                      /* extern */
void clear_object_slot_and_mark_removed();                      /* extern */
void apply_object_setup_and_update(Rec_D_80082D58 *, s32, s32);                            /* extern */


/* Clear the indexed table flag and run the object callbacks in sequence. */
void clear_object_slot_and_run_callbacks(Rec_D_80082D58 *object, s32 callback_arg_1, s32 callback_arg_2) {
    D_80082660[object->unk_60].unk_00 = 0;
    apply_object_setup_and_update(object, callback_arg_1, callback_arg_2);
    unlink_scene_list_node(object);
    func_80033D08(object);
    clear_object_slot_and_mark_removed(object);
}
