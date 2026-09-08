#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_8008F134();                      /* extern */
M2C_UNK func_800C30A4();                      /* extern */

typedef struct S_800CA458_0 {
    s32 unk_00;
    s32 unk_04;
} S_800CA458_0;   /* arg1 in func_800CA458 */


/* Adjust the state values and trigger completion when the object's countdown expires. */
void func_800CA458(Rec_func_80094268_arg0 *object, S_800CA458_0 *state) {
    u16 remainingTicks;

    state->unk_00 = (s32) (state->unk_00 - 0x3333);
    state->unk_04 = (s32) (state->unk_04 + 0x40000);
    remainingTicks = object->unk_6C.as_u16 - 1;
    object->unk_6C.as_u16 = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        func_80033AA8(0x49);
        func_8008F134(object);
        func_800C30A4(object);
    }
}
