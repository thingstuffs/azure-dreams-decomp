/* Configure this callback using its own slot, table addresses and state constants. */
#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

extern s32 D_80081458[];
extern u8 D_800D6674[];
extern u8 D_800D667C[];
extern u8 D_800D66A4[];
extern u8 D_800D66A8[];


void configure_actor_slot_75_and_copy_global(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = D_80081458[0];
    func_800C3050(actor, 0x4B, D_800D66A4, D_800D66A8, D_800D6674,
                  D_800D667C);
}
