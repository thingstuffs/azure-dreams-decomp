#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"


typedef struct S_8009A1A4_2 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_8009A1A4_2;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_44 in initialize_player_linked_record */


extern void D_80099B70();


/* Set up the object using its linked record and assign its next handler. */
void initialize_player_linked_record(Rec_func_80094268_arg0 *object, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) ((S_8009A1A4_2 *)(((Rec_func_80094268_arg0 *)object)->unk_44))->unk_20, object, ptr2);
    object->unk_04.as_pm = &D_80099B70;
}
