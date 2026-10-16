/* Relink of matched town/func_800C8104; every changed retail word is a paired relocation. */
#define D_800C56A8 D_800CA458
#define D_800D5388 D_800D64DC
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void townInitializeObjectEntries();          /* extern */
extern M2C_UNK D_800CA458;
extern M2C_UNK D_800D64DC;


/* Initialize the actor and set its counter to 40 and its handler. */
void func_800CA88C(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    townInitializeObjectEntries(actor, init_param, &D_800D64DC);
    actor->unk_6C.as_s16 = 0x28;
    actor->unk_54 = &D_800CA458;
}
