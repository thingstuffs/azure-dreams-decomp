#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C2E84();          /* extern */
extern M2C_UNK D_800C6644;
extern M2C_UNK D_800D5944;


/* Switch the actor state and callback when the countdown expires, then reset it to five ticks. */
void func_800C6680(Rec_func_80094268_arg0 *actor, M2C_UNK unused, M2C_UNK state_context) {
    u16 ticks_left;

    ticks_left = actor->unk_6C.as_u16 - 1;
    actor->unk_6C.as_u16 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        func_800C2E84(actor, state_context, &D_800D5944);
        actor->unk_54 = &D_800C6644;
        actor->unk_6C.as_u16 = 5U;
    }
}
