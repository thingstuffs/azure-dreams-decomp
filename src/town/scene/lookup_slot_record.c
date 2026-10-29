#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
void func_800176B8(void *, s32);             /* extern */
void initialize_state_two_entries_pointer(s32 bit_index);                         /* extern */
s32 func_8001868C(s32 flagIndex);                         /* extern */
void func_800188E8(s32, s32, s32);   /* extern */

typedef struct S_806D43CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_806D43CC_0;   /* arg0 in lookup_slot_record */

/* Performs conditional object setup before forwarding to func_800176B8. */
void lookup_slot_record(S_806D43CC_0 *object, s32 forwardedValue) {
    if (func_8001868C(F_05_niko_and_gosh) != 0) {
        func_800188E8(F_sbs34_pad16, 2, 2);
        initialize_state_two_entries_pointer(object->unk_18);
    }
    func_800176B8(object, forwardedValue);
}
