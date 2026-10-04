#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082D58.h"

M2C_UNK func_80033D08();                      /* extern */
void func_8008F134();                      /* extern */
void func_800C30A4();                      /* extern */
void func_800C4174(Rec_D_80082D58 *, s32, s32);                            /* extern */


/* Clear the indexed table flag and run the object callbacks in sequence. */
void func_800C4A30(Rec_D_80082D58 *object, s32 callback_arg_1, s32 callback_arg_2) {
    D_80082660[object->unk_60].unk_00 = 0;
    func_800C4174(object, callback_arg_1, callback_arg_2);
    func_8008F134(object);
    func_80033D08(object);
    func_800C30A4(object);
}
