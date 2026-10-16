#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern M2C_UNK D_800CD70C;
extern M2C_UNK D_800D72AC;


/* Initialize the object and set its data pointer and initial field values. */
void townInitializeObjectAndDataPointer(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK init_value) {
    townInitializeObjectEntries(object, init_value, &D_800D72AC);
    object->unk_50.as_pm = &D_800CD70C;
    object->unk_84.as_s16 = 0x50;
    object->unk_6C.as_s16 = 0xD2;
}
