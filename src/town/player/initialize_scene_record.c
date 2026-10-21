#include "common.h"
#include "shared/town_handler.h"

extern s32 D_80093638;
extern u8 town_scene_record_handlers[];

/* Initialize the record and set its first pointer to D_80093638. */
void initialize_scene_record(s32 **record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) &town_scene_record_handlers, (Rec_func_80094268_arg0 *) record, ptr2);
    *record = &D_80093638;
}
