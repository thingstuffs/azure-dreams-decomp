#include "common.h"
#include "m2c_compat.h"

#include "common.h"
#include "records/Rec_func_80036210_arg0.h"


typedef struct S_80036210_2 {
    u8 pad_00[0x80];
    s32 unk_80;
} S_80036210_2;   /* ((Rec_func_80036210_arg0 *)arg0)->unk_74.as_pv in func_80036210 */




M2C_UNK func_80036B10(); /* extern */
extern M2C_UNK D_80081FDC;
extern M2C_UNK D_80082414;
extern M2C_UNK func_8003626C;

/* Initialize the object's runtime state and set its next handler. */
void func_80036210(Rec_func_80036210_arg0 *object) {
    func_80036B10(&D_80082414, &D_80081FDC, object, 0, ((S_80036210_2 *)(((Rec_func_80036210_arg0 *)object)->unk_74.as_pv))->unk_80);
    object->unk_4C = 0;
    object->unk_68 = &func_8003626C;
}
