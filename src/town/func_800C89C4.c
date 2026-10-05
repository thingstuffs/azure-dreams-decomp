#include "common.h"

typedef s32 M2C_UNK;

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);
extern M2C_UNK D_800D5624[];
extern M2C_UNK D_800D562C[];
extern M2C_UNK D_800D5654[];
extern M2C_UNK D_800D5658[];

/* Configure the actor with mode 13 and its associated tables, then set its state flag. */
void func_800C6124(void *actor) {
    func_800C3050(actor, 0xD, D_800D5654, D_800D5658, D_800D5624, D_800D562C);
    *((s8 *)actor + 0x70) = 1;
}
