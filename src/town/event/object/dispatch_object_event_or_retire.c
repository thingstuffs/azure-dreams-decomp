#include "common.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082D58.h"
#include "shared/object_links.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/scene/object.h"


void unlink_node_if_registered(void *block_data);
s32 update_object_and_clear_status_fields();
void set_state_bytes_from_flags(s32 flags, u8 *state);
s32 classify_object_against_bounds(void *, s32);


   /* the 0x2 bytes before arg0 in dispatch_object_event_or_retire, addressed as arg0[-1] */


/* Dispatches an object event or cleans up the object when the event check succeeds. */
void dispatch_object_event_or_retire(void *object_arg, s32 event, s32 event_data)
{
    ObjectRetirementFlags *object = object_arg;
    s32 saved_event = event;
    register s32 saved_event_data = event_data;
    s8 *status_ptr;

    if (classify_object_against_bounds(object, event) != 0) {
        unlink_scene_list_node(object_arg);
        status_ptr = ((Rec_D_80082D58 *)object)->unk_98.as_ps8;
        if (status_ptr != 0) {
            *status_ptr = 0;
        }
        unlink_node_if_registered(object);
        object[-1].flags =
            (u16)(object[-1].flags | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }
    ((Rec_D_80082D58 *)object)->unk_50.as_x151a23(
        object, object, saved_event, saved_event_data);
    if (!(object[-1].flags & 0x8000)) {
        set_state_bytes_from_flags(update_object_and_clear_status_fields(saved_event), object_arg);
    }
}
