/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D5DD4[];
extern u8 D_800D5DDC[];
extern u8 D_800D5E04[];
extern u8 D_800D5E08[];


void configure_actor_slot_28_and_render_state(void *context, s32 unused, u16 *stateWords) {
    func_800C3050(context, 0x1C, D_800D5E04, D_800D5E08, D_800D5DD4,
                  D_800D5DDC);
    stateWords[9] = 0x240;
    stateWords[10] &= ~0x100;
}
