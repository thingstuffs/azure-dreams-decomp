/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];
extern u8 D_800D6B14[];
extern u8 D_800D6B18[];


void configure_actor_slot_73_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x49, D_800D6B14, D_800D6B18, D_800D6AE4,
                  D_800D6AEC);
    stateWords[9] = 0x4;
    stateWords[10] &= ~0x100;
}
