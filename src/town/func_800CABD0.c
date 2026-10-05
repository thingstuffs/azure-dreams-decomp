#include "common.h"

extern void func_800C3050(void *object, s32 slot_index, void *field_58_value, void *field_5c_value, void *field_7c_value, void *field_80_value);

extern s32 D_80081458[];
extern u8 D_800D61C4[];
extern u8 D_800D61CC[];
extern u8 D_800D61F4[];
extern u8 D_800D6200[];

/* Set the actor flag, copy the global value into its state, and configure mode 2 with its tables. */
void func_800C8330(void *actor, s32 unused, void *state) {
    *((s8 *)actor + 0x93) = 1;
    *(s32 *)((u8 *)state + 0x28) = D_80081458[0];
    func_800C3050(actor, 2, D_800D61F4, D_800D6200, D_800D61C4,
                  D_800D61CC);
}
