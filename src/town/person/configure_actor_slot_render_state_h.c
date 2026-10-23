/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D6C4C[];
extern u8 D_800D6C54[];
extern u8 D_800D6C7C[];
extern u8 D_800D6C80[];


/*
 * Configures scene slot 0x15 using the four local setup tables, writes render word 9 to 0x240, and
 * clears bit 0x100 in render word 10.
 */
void configure_actor_slot_21_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x15, D_800D6C7C, D_800D6C80, D_800D6C4C,
                  D_800D6C54);
    stateWords[9] = 0x240;
    stateWords[10] &= ~0x100;
}
