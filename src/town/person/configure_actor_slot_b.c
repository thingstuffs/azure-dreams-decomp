/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D53C4[];
extern u8 D_800D53CC[];
extern u8 D_800D53F4[];
extern u8 D_800D53F8[];


/* Calls func_800C3050 with actor, 0x16, D_800D53F4, D_800D53F8, D_800D53C4, D_800D53CC. */
void configure_actor_slot_22(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x16, D_800D53F4, D_800D53F8, D_800D53C4, D_800D53CC);
}
