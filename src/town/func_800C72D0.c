#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */
M2C_UNK func_800C4174(Rec_D_80082D58 *, M2C_UNK, M2C_UNK);                            /* extern */
extern u8 D_80082660;


/* Clear the indexed table flag and run the object callbacks in sequence. */
void func_800C4A30(Rec_D_80082D58 *object, M2C_UNK callback_arg_1, M2C_UNK callback_arg_2) {
    *((object->unk_60 * 8) + &D_80082660) = 0;
    func_800C4174(object, callback_arg_1, callback_arg_2);
    func_8008F134(object);
    func_80033D08(object);
    func_800C30A4(object);
}
