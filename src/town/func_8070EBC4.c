#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
void func_80016CC4(void);                            /* extern */


/* Run setup and invoke the state callback with 0xF and 0x200. */
s32 run_setup_state_callback(void) {
    func_80016CC4();
    D_80016000->unk_20->callback_2F8(0xF, 0x200);
    return 0;
}
