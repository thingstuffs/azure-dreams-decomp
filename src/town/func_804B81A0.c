#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80017D9C();                /* extern */
M2C_UNK call_helper_with_fixed_id_0x118a();                     /* extern */
s32 func_8001894C();                             /* extern */
extern s16 D_80018AEA;

/* Updates flag 0x511 when the selected flag is clear, then processes the request. */
void update_flag_0x511_from_selection(s32 request_id, M2C_UNK request_arg) {
    if (func_8001894C(D_80018AEA) == 0) {
        call_helper_with_fixed_id_0x118a(0x511);
    }
    func_80017D9C(request_id, request_arg);
}
