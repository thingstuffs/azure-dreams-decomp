#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern M2C_UNK D_800C5ADC;
extern M2C_UNK D_800D54BC;


/* Initialize the actor, clear its table flag, and install its handler. */
void func_800C5944(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D54BC);
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5ADC;
}
