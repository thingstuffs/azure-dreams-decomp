/* Relink of matched town/func_800C7FC4; every changed retail word is a paired relocation. */
#define D_80082710 D_80082688
#define D_800C5620 D_800CE08C
#define D_800D5360 D_800D72AC
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern s8 D_80082688;
extern M2C_UNK D_800CE08C;
extern M2C_UNK D_800D72AC;


/* Initialize the actor, clear the shared flag, and set its handler and counter. */
void func_800CE94C(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D72AC);
    D_80082688 = 0;
    actor->unk_54 = &D_800CE08C;
    actor->unk_6C.as_s16 = 0x15;
}
