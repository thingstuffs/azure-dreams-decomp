#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
extern M2C_UNK D_800A7950;


/* Set the object state and initialize both fields with the generated value. */
void func_800A790C(Rec_func_80094268_arg0 *object) {
    s16 initial_value;

    object->unk_50.as_pm = &D_800A7950;
    initial_value = func_800374F4(0x60) + 0xC0;
    object->unk_90.as_s16 = initial_value;
    object->unk_6C.as_s16 = initial_value;
}
