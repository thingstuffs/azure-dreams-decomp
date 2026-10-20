#include "script_symbols.h"
#include "common.h"

extern s32 func_8001868C();
extern void initialize_state_two_entries_pointer();
extern s32 func_800177CC();
extern void func_80016FD0();

/* Apply the object's flag when flag 0x145B is set, then process its action and handle failure. */
s32 process_entry_list_mode_1(void *object, s32 actionParameter) {
    if (func_8001868C(F_selfy_get_tamago) != 0) {
        initialize_state_two_entries_pointer(*(s16 *)((u8 *)object + 0x18));
    }
    if (func_800177CC(object, actionParameter) == 0) {
        func_80016FD0();
        return 0;
    }
    return 1;
}
