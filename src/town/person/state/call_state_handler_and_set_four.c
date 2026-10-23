#include "common.h"

/* extern */
extern s8 person_slot_reset_byte;

typedef struct S_800CEAC8_0 {
    u8 pad_00[0x90];
    s16 unk_90;
} S_800CEAC8_0;   /* arg0 in call_state_handler_and_set_four */
void func_800CEB00(S_800CEAC8_0 *, s32, s32);
/* Call func_800CEB00, clear D_80082688, and set the object state to 4. */
void call_state_handler_and_set_four(S_800CEAC8_0 *object, s32 context, s32 update_data) {
    func_800CEB00(object, context, update_data);
    person_slot_reset_byte = 0;
    object->unk_90 = 4;
}
