/* Relink of matched town/func_800C86A0; every changed retail word is a paired relocation. */
#define D_800D5540 D_800D5568
#include "common.h"
#include "m2c_compat.h"

void func_800C2E84();          /* extern */
void func_800C58F4();       /* extern */
extern M2C_UNK D_800D5568;

/* Initialize the actor with the state table and run its follow-up handler. */
void func_800C5EB8(s32 actor, s32 context, s32 state_context) {
    func_800C2E84(actor, state_context, &D_800D5568);
    func_800C58F4(actor, context, state_context);
}
