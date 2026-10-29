#include "common.h"
#include "records/Rec_func_80094268_arg0.h"



typedef struct S_800C4174_1 {
    u8 pad_00[0x4];
    s32 *unk_04;
} S_800C4174_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in apply_object_setup_and_update */


#include "town/person/object/initialize_object_entries_api.h"
#include "town/person/object_setup.h"
#include "town/person/object.h"
void install_object_handler_and_clear_slot_flag(void *object, void *update_context, void *setup_context);


/* Apply setup from the object descriptor and then run the object update. */
void apply_object_setup_and_update(void *object, void *update_context, void *setup_context) {
    initialize_object_entries(object, setup_context, ((S_800C4174_1 *)(((Rec_func_80094268_arg0 *)object)->unk_80))->unk_04);
    install_object_handler_and_clear_slot_flag(object, update_context, setup_context);
}
