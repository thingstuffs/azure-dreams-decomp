/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"

extern void func_800C3050(void *object, u32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D6AE4[];
extern u8 D_800D6AEC[];
extern u8 D_800D6B14[];
extern u8 D_800D6B18[];


/*
 * Configures scene slot 72 with the four local tables, stores 4 in render halfword 9, and clears
 * flag 0x100 in halfword 10.
 */
void configure_actor_slot_72_and_render_state(void *context, void *unused, struct SpriteFrameState *stateWords) {
    func_800C3050(context, 0x48, D_800D6B14, D_800D6B18, D_800D6AE4,
                  D_800D6AEC);
    stateWords->clut = 0x4;
    stateWords->flags &= ~0x100;
}
