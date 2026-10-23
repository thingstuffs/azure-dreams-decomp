/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D71C4[];
extern u8 D_800D71CC[];
extern u8 D_800D71F4[];
extern u8 D_800D71F8[];


/*
 * Configures scene slot 64 with the four local tables, stores 0x280 in render halfword 9, and
 * clears flag 0x100 in halfword 10.
 */
void configure_actor_slot_64_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x40, D_800D71F4, D_800D71F8, D_800D71C4,
                  D_800D71CC);
    stateWords[9] = 0x280;
    stateWords[10] &= ~0x100;
}
