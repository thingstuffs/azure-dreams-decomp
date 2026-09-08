#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_80094984();           /* extern */
extern M2C_UNK D_80090F00;
extern M2C_UNK D_800D00C0;


/* Initialize the object with its data pointer and type value 6. */
void func_80094330(Rec_func_80094268_arg0 *object) {
    func_80094984(&D_800D00C0, object);
    object->unk_00.as_pm = &D_80090F00;
    object->unk_0A.as_s16 = 6;
}
