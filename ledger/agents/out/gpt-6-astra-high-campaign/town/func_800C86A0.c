#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800C2E84();          /* extern */
M2C_UNK func_800C58F4();       /* extern */
extern M2C_UNK D_800D5540;

/* Initialize the actor with the state table and run its follow-up handler. */
void func_800C5E00(s32 actor, M2C_UNK context, M2C_UNK state_context) {
    func_800C2E84(actor, state_context, &D_800D5540);
    func_800C58F4(actor, context, state_context);
}
