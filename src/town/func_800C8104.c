#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C56A8;
extern M2C_UNK D_800D5388;


/* Initialize the actor and set its counter to 40 and its handler. */
void func_800C5864(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D5388);
    actor->unk_6C.as_s16 = 0x28;
    actor->unk_54 = &D_800C56A8;
}
