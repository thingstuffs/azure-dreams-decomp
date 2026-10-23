/* G00680: actor slot global state. */
/* Original-file evidence (G00680): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6674, PD:town/engine:800D667C, PD:town/engine:800D66A4, PD:town/engine:800D66A8. */
#include "town/person/actor_slot_global_state_g00680.h"

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 75 with the four local tables.
 */
void configure_actor_slot_75_and_copy_global(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = loaded_town_resource_attributes[0];
    func_800C3050(actor, 0x4B, D_800D66A4, D_800D66A8, D_800D6674,
                  D_800D667C);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 76 with the four local tables.
 */
void configure_actor_slot_76_and_copy_global(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = loaded_town_resource_attributes[0];
    func_800C3050(actor, 0x4C, D_800D66A4, D_800D66A8, D_800D6674,
                  D_800D667C);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 77 with the four local tables.
 */
void configure_actor_slot_77_and_copy_global(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = loaded_town_resource_attributes[0];
    func_800C3050(actor, 0x4D, D_800D66A4, D_800D66A8, D_800D6674,
                  D_800D667C);
}

/*
 * Sets actor byte 0x93 to one, copies loaded_town_resource_attributes[0] into the output state,
 * and configures scene slot 78 with the four local tables.
 */
void configure_actor_slot_78_and_copy_global(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = loaded_town_resource_attributes[0];
    func_800C3050(actor, 0x4E, D_800D66A4, D_800D66A8, D_800D6674,
                  D_800D667C);
}
