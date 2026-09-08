#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

M2C_UNK func_8009F644(); /* extern */
M2C_UNK func_800A56E0();                     /* extern */


/* Reset object state, clear flag 0x10, and invoke the state handlers. */
void func_8008FA14(Rec_func_8008ACDC_arg0 *object, M2C_UNK unusedArg1, M2C_UNK unusedArg2, M2C_UNK handlerContext) {
    object->unk_9A.as_s8 = 0x20;
    object->unk_9B.as_s8 = 0;
    object->unk_8C.as_s32 = 0;
    func_800A56E0(0x512);
    object->unk_A2 = (u16) (object->unk_A2 & 0xFFEF);
    func_8009F644(handlerContext, 0x30, object->unk_96.as_s16, 0);
}
