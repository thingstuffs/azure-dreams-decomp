#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008F2D4_arg0.h"
#include "records/Rec_func_8008F2D4_arg1.h"

/* Sets the control flag and initializes the record with a value and a cleared trailing field. */
void func_8008F50C(Rec_func_8008F2D4_arg0 *control, Rec_func_8008F2D4_arg1 *record, s32 initial_value) {
    control->unk_37 = 1;
    record->unk_00 = initial_value;
    record->unk_0C = 0;
}
