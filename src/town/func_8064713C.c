#include "common.h"

extern void func_800176A0(s32);
extern void func_80016C64(void *, void *, s32, s32);
extern u8 D_8001798C[];
extern u8 D_80017B30[];

/* Call func_800176A0(0x12C7), then forward the inputs to func_80016C64 with D_8001798C and D_80017B30. */
void func_8001613C(s32 input_value, s32 unused, s32 extra_value) {
    func_800176A0(0x12C7);
    func_80016C64(D_8001798C, D_80017B30, input_value, extra_value);
}
