#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80025850_arg0.h"

void func_80025D9C();       /* extern */
void func_80025E3C();                 /* extern */
void func_80025FFC(void *, s32, s32, s32);                            /* extern */


/* Initialize the object and configure it from its embedded data and stored value. */
void func_80026084(void *object, s32 init_value, s32 init_value_2, s32 init_value_3) {
    func_80025FFC(object, init_value, init_value_2, init_value_3);
    func_80025D9C(object, object + 0x44, object + 0x1C, object + 0x2C);
    func_80025E3C(object, ((Rec_func_80025850_arg0 *)object)->unk_54);
}
