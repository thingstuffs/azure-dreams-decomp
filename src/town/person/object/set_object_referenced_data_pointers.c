#include "common.h"
#include "town/person/actor_data_references_g00663.h"
#include "records/Rec_func_80094268_arg0.h"
#include "m2c_compat.h"


typedef struct S_800C641C_2 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C641C_2;   /* ((S_800C641C_1 *)arg0)->unk_80 in set_object_referenced_data_pointers */


extern M2C_UNK D_800D5820;
extern M2C_UNK D_800D5844;


/* Sets the object's referenced data pointers to the static data blocks. */
void set_object_referenced_data_pointers(Rec_func_80094268_arg0 *object, void *unused_context, struct SpriteFrameState *unused_sprite) {
    /* BYTES: retain the two callback operands forwarded by the slot initializer. */
    *object->unk_7C.as_pps32 = &D_800D5820;
    ((S_800C641C_2 *)object->unk_80)->unk_04 = &D_800D5844;
}
