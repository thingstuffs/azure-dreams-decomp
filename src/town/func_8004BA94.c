/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D6430[];
extern u8 D_800D6438[];
extern u8 D_800D6460[];
extern u8 D_800D6464[];


void configure_actor_slot_26_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x1A, D_800D6460, D_800D6464, D_800D6430,
                  D_800D6438);
    stateWords[9] = 0x2C0;
    stateWords[10] &= ~0x100;
}
