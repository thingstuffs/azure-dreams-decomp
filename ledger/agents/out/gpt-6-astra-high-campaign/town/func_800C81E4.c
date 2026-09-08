#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern u8 D_80082660;
extern M2C_UNK D_800C5ADC;
extern M2C_UNK D_800D54BC;


/* Initialize the actor, clear its table flag, and install its handler. */
void func_800C5944(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D54BC);
    *((actor->unk_60 * 8) + &D_80082660) = 0;
    actor->unk_54 = &D_800C5ADC;
}
