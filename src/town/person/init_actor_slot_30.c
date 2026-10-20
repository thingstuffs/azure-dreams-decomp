#include "common.h"

extern void initialize_object_and_register_slot(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D517C[];
extern u8 D_800D5184[];
extern u8 D_800D51AC[];
extern u8 D_800D51B0[];

/* Configure the actor with type 0x30 and its data tables. */
void init_actor_slot_30(void *actor) {
    initialize_object_and_register_slot(actor, 0x30, D_800D51AC, D_800D51B0, D_800D517C, D_800D5184);
}
