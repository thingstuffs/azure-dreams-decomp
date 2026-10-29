#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "town/person.h"
#include "town/person/object.h"


typedef struct S_800C838C_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800C838C_1;   /* ((Rec_func_80094268_arg0 *)arg0)->unk_80 in initialize_object_configuration_x */


extern M2C_UNK D_800D6244;
extern u8 D_800D62D8;
extern u8 D_800D62E0;
extern u8 D_800D6308;
extern u8 D_800D630C;


/* Initialize the object with configuration 0xA and set its associated data pointer. */
void initialize_object_configuration_x(PersonObject *object) {
    initialize_object_and_register_slot(object, 0xA, &D_800D6308, &D_800D630C, &D_800D62D8, &D_800D62E0);
    object->descriptor->entries[1] = &D_800D6244;
}
