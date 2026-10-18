#include "common.h"
void run_object_handlers_supplied_state(s32 object, s32 state, s32 context);

typedef struct S_800C88AC_0 {
    u8 pad_00[0x54];
    s32 * unk_54;
} S_800C88AC_0;   /* arg0 in func_800C88AC */
void func_800C4804(S_800C88AC_0 *, s32, s32);
/* Call func_800C4804 and set the object pointer to run_object_handlers_supplied_state. */
void func_800C88AC(S_800C88AC_0 *object, s32 param_1, s32 param_2) {
    func_800C4804(object, param_1, param_2);
    object->unk_54 = &run_object_handlers_supplied_state;
}
