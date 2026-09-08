#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660[];
extern M2C_UNK D_800CB21C;
extern M2C_UNK D_800D6910;


/* Initialize the object's state, clear its slot flag, and set its counter to seven. */
void func_800CB27C(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context) {
    func_800C2E84(object, context, &D_800D6910);
    D_80082660[object->unk_60 * 8] = 0;
    object->unk_54 = &D_800CB21C;
    object->unk_6C.as_s16 = 7;
}
