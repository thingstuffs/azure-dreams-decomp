#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern u8 D_800D517C[];
extern u8 D_800D5184[];
extern u8 D_800D51AC[];
extern u8 D_800D51B0[];

/* Configure the actor with type 0x30 and its data tables. */
void func_800C5368(void *actor) {
    func_800C3050(actor, 0x30, D_800D51AC, D_800D51B0, D_800D517C, D_800D5184);
}
