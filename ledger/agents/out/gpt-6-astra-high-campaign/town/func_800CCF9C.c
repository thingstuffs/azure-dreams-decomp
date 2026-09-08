#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern s8 D_800826B8;
extern M2C_UNK D_800CA114;
extern M2C_UNK D_800D6540;


/* Initialize the object, clear the shared flag, and set its callback. */
void func_800CA6FC(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    func_800C2E84(object, context, &D_800D6540);
    D_800826B8 = 0;
    object->unk_54 = &D_800CA114;
}
