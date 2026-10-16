/* Relink of matched town/func_800C7FC4; every changed retail word is a paired relocation. */
#define D_80082710 D_800826B8
#define D_800C5620 D_800C9F1C
#define D_800D5360 D_800D6504
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern s8 D_800826B8;
extern M2C_UNK D_800C9F1C;
extern M2C_UNK D_800D6504;


/* Initialize the actor, clear the shared flag, and set its handler and counter. */
void func_800CA51C(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D6504);
    D_800826B8 = 0;
    actor->unk_54 = &D_800C9F1C;
    actor->unk_6C.as_s16 = 0x15;
}
