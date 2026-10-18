#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "shared/types3a_types.h"


void func_80033D08(void *block_data);
void unlink_scene_list_node();
s32 update_object_and_clear_status_fields();
void set_state_bytes_from_flags();
s32 classify_object_against_bounds(void *, s32);


   /* the 0x2 bytes before arg0 in dispatch_object_event_or_retire, addressed as arg0[-1] */


/* Dispatches an object event or cleans up the object when the event check succeeds. */
void dispatch_object_event_or_retire(void *object, s32 event, s32 event_data)
{
    s32 saved_event = event;
    register s32 saved_event_data = event_data;
    s8 *status_ptr;

    if (classify_object_against_bounds(object, event) != 0) {
        unlink_scene_list_node(object);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != 0) {
            *status_ptr = 0;
        }
        func_80033D08(object);
        ((ObjectRetirementFlags *)object)[-1].unk_00 =
            (u16)(((ObjectRetirementFlags *)object)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(
        object, object, saved_event, saved_event_data);
    if (!(((ObjectRetirementFlags *)object)[-1].unk_00 & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(saved_event), object);
    }
}
