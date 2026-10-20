/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/town_handler.h"

typedef struct S_80099CE0_2 {
    u8 pad_00[0x14];
    s32 unk_08;
} S_80099CE0_2;   

extern s32 D_80099874;

void func_80099ED0(Rec_func_80094268_arg0 *object, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) ((S_80099CE0_2 *)(((Rec_func_80094268_arg0 *)object)->unk_44))->unk_08, object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &D_80099874;
    object->unk_10.as_s16 = 0xC00;
}
