#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80027AD0_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80028050();       /* extern */
M2C_UNK func_800280FC();                 /* extern */
M2C_UNK func_80028210(void *, s32, s32, s32);                            /* extern */


/* Initialize the object and configure it from its embedded data and stored value. */
void func_8002823C(void *object, s32 init_value, s32 init_value_2, s32 init_value_3) {
    func_80028210(object, init_value, init_value_2, init_value_3);
    func_80028050(object, object + 0x78, object + 0x50, object + 0x60);
    func_800280FC(object, ((Rec_func_80027AD0_arg0 *)object)->unk_88);
}
