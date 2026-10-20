#include "script_symbols.h"
#include "common.h"

s32 func_800177CC(s32, s32);
s32 initialize_state_two_entries_pointer();                         /* extern */
s32 func_8001860C(s32);
s32 call_points();                         /* extern */
s32 func_80018800();                         /* extern */

typedef struct S_806D435C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D435C_0;   /* arg0 in process_object_conditionally_passing_stored */

/* Processes the object, conditionally passing its stored value to initialize_state_two_entries_pointer. */
void process_object_conditionally_passing_stored(S_806D435C_0 *object, s32 context) {
    func_8001860C(F_sbs34_pad15);
    if ((call_points(5) != 0) || (func_80018800(5) != 0)) {
        initialize_state_two_entries_pointer(object->unk_18);
    }
    func_800177CC(object, context);
}
