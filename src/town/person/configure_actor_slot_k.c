/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D72FC[];
extern u8 D_800D7304[];
extern u8 D_800D732C[];
extern u8 D_800D7338[];


/* Calls func_800C3050 with actor, 0x5, D_800D732C, D_800D7338, D_800D72FC, D_800D7304. */
void configure_actor_slot_5(void *actor) {
    func_800C3050(actor, 0x5, D_800D732C, D_800D7338, D_800D72FC, D_800D7304);
}
