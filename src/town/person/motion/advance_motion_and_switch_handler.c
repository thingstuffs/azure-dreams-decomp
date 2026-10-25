#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"


typedef struct S_800C3F44_3 {
    u8 pad_00[0x20];
    s32 *unk_20;
} S_800C3F44_3;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in advance_motion_and_switch_handler */


void add_hex_20000_s_signed_offset_hex_14(EntityRec *record);                      /* extern */
#include "town/person/object/initialize_object_entries_api.h"        /* extern */
extern void D_800C3EAC();


/* Advances motion and changes the object handler when the motion step is nonnegative. */
void advance_motion_and_switch_handler(Rec_func_80094268_arg0 *object, EntityRec *motion, void *context) {
    motion->z.v = (s32) (motion->z.v + motion->flags14);
    add_hex_20000_s_signed_offset_hex_14(motion);
    if (motion->flags14 >= 0) {
        initialize_object_entries((Struct800C5724 *)(object), context, ((S_800C3F44_3 *)object->unk_80)->unk_20);
        object->unk_54 = &D_800C3EAC;
    }
}
