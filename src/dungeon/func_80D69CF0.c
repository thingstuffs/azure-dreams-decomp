#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_func_800A9E70_arg0.h"

s32 func_800A2B5C();                          /* extern */
M2C_UNK func_800A4ACC();                      /* extern */
extern u16 D_80083462;



/* Clears the object's high flag bit and conditionally resets state and decrements its counter. */
void func_801754F0(Rec_func_800A9E70_arg0 *state, M2C_UNK unused_1, M2C_UNK unused_2, Rec_D_800E3D7C *object) {
    object->unk_71.as_u8 = (u8) (object->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2B5C(object) << 0x10) == 0) && ((func_800A2B5C(object) << 0x10) == 0)) {
        state->unk_8C = 0;
        state->unk_9A.as_s8 = 0x17;
        state->unk_9B.as_s8 = 0;
        state->unk_96.as_s16 = 0;
        func_800A4ACC(object);
        object->unk_6D.as_u8 = (u8) (object->unk_6D.as_u8 - 1);
    }
}
