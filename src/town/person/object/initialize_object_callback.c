#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"


#include "town/person/object/initialize_object_entries_api.h"
extern M2C_UNK D_800C8788;
extern M2C_UNK D_800D627C;


typedef struct S_800C8808_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C8808_1;   /* arg1 in initialize_object_callback */

/* Initialize the object callback and set its state value to negative ten in fixed point. */
void initialize_object_callback(Rec_func_80094268_arg0 *object, S_800C8808_1 *state, s32 init_data) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(init_data), &D_800D627C);
    object->unk_54 = &D_800C8788;
    state->unk_14 = 0xFFF60000;
}
