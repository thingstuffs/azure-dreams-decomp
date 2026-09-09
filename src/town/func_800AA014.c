#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A77D0;

typedef struct S_800A7774_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x3C];
    u16 unk_90;
} S_800A7774_0;   /* arg0 in func_800A7774 */


M2C_UNK func_80033D08(S_800A7774_0 *, s32);
/* Decrement the countdown and reset it to ten while changing the handler when it expires. */
void func_800A7774(S_800A7774_0 *object, s32 value) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_90 - 1;
    object->unk_90 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_80033D08(object, value);
        object->unk_90 = 0xAU;
        object->unk_50 = &D_800A77D0;
    }
}
