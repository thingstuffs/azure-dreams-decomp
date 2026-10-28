/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"
#include "shared/sprite_frame_state.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D57E8[];
extern u8 D_800D57F0[];
extern u8 D_800D5818[];
extern u8 D_800D581C[];


/* Calls func_800C3050 with actor, 0x20, D_800D5818, D_800D581C, D_800D57E8, D_800D57F0. */
void configure_actor_slot_32(void *actor, void *unused_position, struct SpriteFrameState *unused_sprite) {
    func_800C3050(actor, 0x20, D_800D5818, D_800D581C, D_800D57E8, D_800D57F0);
}
