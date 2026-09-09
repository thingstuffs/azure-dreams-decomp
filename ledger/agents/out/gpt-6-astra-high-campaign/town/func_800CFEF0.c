#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"

s32 func_800374F4();                         /* extern */
s32 *func_8008FAC0();              /* extern */
s32 func_800C30E0(Rec_func_80094268_arg0 *, M2C_UNK, M2C_UNK, s32);                                /* extern */
M2C_UNK func_800CDDFC();    /* extern */
M2C_UNK func_800CDE4C();    /* extern */
extern M2C_UNK D_800CFCB4;

/* Count down when the object is ready and choose its next setup when the timer expires. */
void func_800CD650(Rec_func_80094268_arg0 *object, M2C_UNK request_data, M2C_UNK request_param, s32 check_param) {
    s32 *state;
    u16 ticks_left;

    if ((func_800C30E0(object, request_data, request_param, check_param) == 0) &&
        ((state = func_8008FAC0(object, &D_800CFCB4), (state == NULL)) || (*state == 2)) &&
        (ticks_left = object->unk_6C.as_u16 - 1,
         object->unk_6C.as_u16 = ticks_left, ((ticks_left << 0x10) <= 0))) {
        if (func_800374F4(2) & 0xFFFF) {
            func_800CDDFC(object, request_data, request_param);
            return;
        }
        func_800CDE4C(object, request_data, request_param);
    }
}
