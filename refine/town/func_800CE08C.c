#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB73C(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_800CBB68();                /* extern */


/* Decrement the actor's countdown and run its expiration actions when it expires. */
void func_800CB7EC(Rec_func_80094268_arg0 *actor, M2C_UNK action_arg1, M2C_UNK action_arg2) {
    u16 countdown;

    countdown = actor->unk_6C.as_u16 - 1;
    actor->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB73C(actor);
        func_800CBB68(actor->unk_96.as_s8, actor->unk_88, actor->unk_8A);
        func_800C4174(actor, action_arg1, action_arg2);
    }
}
