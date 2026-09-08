#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C9864;
extern M2C_UNK D_800D64DC;


/* Initialize the object and set its handler. */
void func_800C9C54(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    func_800C2E84(object, context, &D_800D64DC);
    object->unk_50.as_pm = &D_800C9864;
}
