/* Relink of matched town/func_800C7FC4; every changed retail word is a paired relocation. */
#define D_800D5360 D_800D53B0
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

void func_800C2E84();          /* extern */
extern s8 D_80082710;
extern M2C_UNK D_800C5620;
extern M2C_UNK D_800D53B0;


/* Initialize the actor, clear the shared flag, and set its handler and counter. */
void func_800C57C4(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK init_param) {
    func_800C2E84(actor, init_param, &D_800D53B0);
    D_80082710 = 0;
    actor->unk_54 = &D_800C5620;
    actor->unk_6C.as_s16 = 0x15;
}
