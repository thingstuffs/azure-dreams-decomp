#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"



s32 func_80016CC4(void);
void initialize_resources_assigns_pointer_lookup();                            /* extern */


/* Run both setup routines and invoke the state callback with 0xE and 0x200. */
s32 run_setup_routines_state_callback(void) {
    func_80016CC4();
    initialize_resources_assigns_pointer_lookup();
    D_80016000->unk_20->callback_2F8(0xE, 0x200);
    return 0;
}
