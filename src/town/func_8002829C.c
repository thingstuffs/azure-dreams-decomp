/* Relink of matched town/func_800C81E4; every changed retail word is a paired relocation. */
#define D_800C5ADC D_800C5C70
#define D_800D54BC D_800D54D4
#include "common.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern M2C_UNK D_800C5C70;
extern M2C_UNK D_800D54D4;


/* Initialize the actor, clear its table flag, and install its handler. */
void func_800C59FC(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    townInitializeObjectEntries(actor, init_param, &D_800D54D4);
    D_80082660[actor->unk_60].unk_00 = 0;
    actor->unk_54 = &D_800C5C70;
}
