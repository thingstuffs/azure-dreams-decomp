/* cfail-repair: true-space rowbase definition */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "records/Rec_D_80082E80.h"

M2C_UNK func_800C2CB0();
s32 func_800C2D0C();



/* Store the value table, apply the selected value to the target, and clear its status byte. */
void func_800C2D34(Rec_func_80094268_arg0 *object, Rec_D_80082E80 *target, s32 *value_table) {
    object->unk_78 = value_table;
    func_800C2CB0(object, target, object->unk_78[func_800C2D0C(object->unk_72.as_s16)], 0);
    target->unk_05.as_s8 = 0;
}
