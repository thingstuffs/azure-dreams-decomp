#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A0668_arg0.h"

M2C_UNK func_800A0B74();                 /* extern */
M2C_UNK into_dn_door_jobs();                            /* extern */
M2C_UNK func_800A12B4(); /* extern */
extern M2C_UNK D_800A08E8;
extern M2C_UNK D_80100B70;


typedef struct S_800A0E3C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
} S_800A0E3C_1;   /* arg1 in func_800A0E3C */

/* Update the countdown and reset the object's state when it expires. */
void func_800A0E3C(Rec_func_800A0668_arg0 *object, S_800A0E3C_1 *source, M2C_UNK update_arg_a, M2C_UNK update_arg_b) {
    u16 remaining_count;

    func_800A12B4(&D_80100B70, update_arg_a, update_arg_b);
    remaining_count = object->unk_6C - 1;
    object->unk_6C = remaining_count;
    if ((remaining_count << 0x10) <= 0) {
        func_800A0B74(object, source->unk_48);
        object->unk_50 = &D_800A08E8;
        into_dn_door_jobs();
    }
}
