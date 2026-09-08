#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_8008F134();                      /* extern */
s32 func_8009CFE0(Rec_func_80094268_arg0 *, M2C_UNK);                                /* extern */
M2C_UNK func_800C30A4();                      /* extern */
M2C_UNK func_800C321C();    /* extern */
extern M2C_UNK D_800C3960;


/* Update the object motion or clear its state and clean it up when the position check fails. */
void func_800C3174(Rec_func_80094268_arg0 *object, M2C_UNK position, M2C_UNK motion) {
    s32 check_result;
    s8 *state_flag;

    check_result = func_8009CFE0(object, position);
    if (check_result != 0) {
        if ((check_result != 2) || (object->unk_50.as_s32 != &D_800C3960)) {
            func_8008F134(object);
            state_flag = object->unk_98;
            if (state_flag != NULL) {
                *state_flag = 0;
            }
            func_80033D08(object);
            func_800C30A4(object);
            return;
        }
        func_800C321C(object, position, motion);
        return;
    }
    func_800C321C(object, position, motion);
}
