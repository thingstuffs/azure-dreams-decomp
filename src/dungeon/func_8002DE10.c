/* Relink of matched town/func_8002DE10; every changed retail word is a paired relocation. */
/* Relink of matched town/func_800C90B4; every changed retail word is a paired relocation. */
#define set_object_referenced_data_pointers set_linked_data_pointer
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void apply_object_setup_and_update();    /* extern */
extern void set_linked_data_pointer(void *);                            /* extern */


/* Decrement the record's countdown and run its follow-up calls when it expires. */
void func_800CB570(Rec_func_80094268_arg0 *record, s32 forward_arg1, s32 forward_arg2) {
    u16 countdown;

    countdown = record->unk_6C.as_u16 - 1;
    record->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        set_linked_data_pointer(record);
        apply_object_setup_and_update(record, forward_arg1, forward_arg2);
    }
}
