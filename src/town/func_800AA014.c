#include "common.h"
#include "m2c_compat.h"

/* extern */
extern M2C_UNK D_800A77D0;

typedef struct S_800A7774_0 {
    u8 pad_00[0x50];
    s32 * unk_50;
    u8 pad_54[0x3C];
    u16 unk_90;
} S_800A7774_0;   /* arg0 in decrement_effect_timer_and_switch */


void func_80033D08(void *block_data);
/* Decrement the countdown and reset it to ten while changing the handler when it expires. */
void decrement_effect_timer_and_switch(S_800A7774_0 *object, s32 value) {
    u16 remaining_ticks;

    remaining_ticks = object->unk_90 - 1;
    object->unk_90 = remaining_ticks;
    if ((remaining_ticks << 0x10) <= 0) {
        func_80033D08(object);
        object->unk_90 = 0xAU;
        object->unk_50 = &D_800A77D0;
    }
}
