#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_80082680;
extern M2C_UNK D_800C7E70;
extern M2C_UNK D_800D5FE8;


/* Initialize the object state, callback, countdown, and starting value. */
void func_800C8000(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK init_data) {
    func_800C2E84(object, init_data, &D_800D5FE8);
    D_80082680 = 0;
    object->unk_54 = &D_800C7E70;
    object->unk_6C.as_s16 = 0xA;
    object->unk_72.as_s16 = 0xC00;
}
