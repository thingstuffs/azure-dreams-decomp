#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

M2C_UNK func_800C4174();    /* extern */
M2C_UNK func_800CB708(Rec_func_80094268_arg0 *);                            /* extern */
M2C_UNK func_800CB8CC();                  /* extern */


/* Decrement the entity countdown and run its completion handlers when it expires. */
void func_800CB0F0(Rec_func_80094268_arg0 *entity, M2C_UNK completion_arg1, M2C_UNK completion_arg2) {
    u16 countdown;

    countdown = entity->unk_6C.as_u16 - 1;
    entity->unk_6C.as_u16 = countdown;
    if ((countdown << 0x10) <= 0) {
        func_800CB708(entity);
        func_800CB8CC(entity, entity->unk_96.as_u8);
        func_800C4174(entity, completion_arg1, completion_arg2);
    }
}
