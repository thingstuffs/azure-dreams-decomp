#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
void func_80018BD0(s32);                     /* extern */


/* Reset two flags and invoke the state callback with 0x10 and 0x200. */
s32 reset_two_flags_state_callback(void) {
    func_80018BD0(0xFB7);
    func_80018BD0(0xFB8);
    D_80016000->unk_20->callback_2F8(0x10, 0x200);
    return 0;
}
