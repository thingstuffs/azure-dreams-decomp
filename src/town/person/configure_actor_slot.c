/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D5328[];
extern u8 D_800D5330[];
extern u8 D_800D5358[];
extern u8 D_800D535C[];


void configure_actor_slot_16(void *actor) {
    func_800C3050(actor, 0x10, D_800D5358, D_800D535C, D_800D5328, D_800D5330);
}
