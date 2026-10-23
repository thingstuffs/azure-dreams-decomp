#include "script_symbols.h"
#include "common.h"

s32 func_80017D9C(s32, s32);
s32 call_helper_with_fixed_id_0x118a(s32);
s32 func_8001894C();                             /* extern */
extern s16 scene_request_flag_id;

/* Updates flag 0x511 when the selected flag is clear, then processes the request. */
void update_flag_0x511_from_selection(s32 request_id, s32 request_arg) {
    if (func_8001894C(scene_request_flag_id) == 0) {
        call_helper_with_fixed_id_0x118a(F_sbs07_pad26);
    }
    func_80017D9C(request_id, request_arg);
}
