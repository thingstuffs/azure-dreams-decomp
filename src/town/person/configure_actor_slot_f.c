/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D7238[];
extern u8 D_800D7240[];
extern u8 D_800D7268[];
extern u8 D_800D726C[];


void configure_actor_slot_14(void *actor) {
    func_800C3050(actor, 0xE, D_800D7268, D_800D726C, D_800D7238, D_800D7240);
}
