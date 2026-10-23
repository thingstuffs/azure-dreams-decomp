#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

#include "town/person/object/initialize_object_entries_api.h"          /* extern */
extern s8 D_80082688;
extern M2C_UNK D_800CE780;
extern s32 D_800D72D4[];


typedef struct S_800CECC8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800CECC8_1;   /* arg1 in initialize_object_with_handler_and_offset */

/* Initialize the object, clear the global flag, and set its handler and initial offset. */
void initialize_object_with_handler_and_offset(Rec_func_80094268_arg0 *object, S_800CECC8_1 *motion, s32 init_data) {
    initialize_object_entries((Struct800C5724 *)(object), (s8 *)(init_data), &D_800D72D4);
    D_80082688 = 0;
    object->unk_54 = &D_800CE780;
    motion->unk_14 = 0xFFF60000;
}
