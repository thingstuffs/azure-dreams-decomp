/* Relink of matched town/func_800C86A0; every changed retail word is a paired relocation. */
#define D_800D5540 D_800D5554
#include "common.h"
#include "m2c_compat.h"

void townInitializeObjectEntries();          /* extern */
void func_800C58F4();       /* extern */
extern M2C_UNK D_800D5554;

/* Initialize the actor with the state table and run its follow-up handler. */
void func_800C5E5C(s32 actor, s32 context, s32 state_context) {
    townInitializeObjectEntries(actor, state_context, &D_800D5554);
    func_800C58F4(actor, context, state_context);
}
