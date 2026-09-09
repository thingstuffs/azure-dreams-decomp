#include "common.h"

extern void *func_8003FC64();
extern s32 func_800269E8();
extern s32 func_800267B0();
extern void func_800269A0();
extern void func_8004491C();
extern void func_8004B1A4();
extern u8 D_8004CAA0[];
extern s32 D_800814A0;

/* Allocate and initialize a child object, releasing its resource if initialization fails. */
void *func_80026A64(s32 parent_object, s32 type_code, s32 config_value) {
    u8 *object;
    u8 *state;

    object = func_8003FC64(0);
    state = object + 0x20;
    if (object != 0) {
        if (func_800269E8(state) != 0) {
            *(void **)(object + 0xC) = object + 0x80;
            *(s32 *)(state + 0x6C) = func_800267B0(*(s32 *)(state + 0x70));
            func_800269A0(state, parent_object, type_code, config_value);
            func_8004491C(object, D_8004CAA0);
        } else {
            func_8004B1A4(*(s32 *)(state + 0x74));
            *(u16 *)(object + 0x1E) |= 0x8000;
            object = 0;
            D_800814A0 |= 0x8000;
        }
    }
    return object;
}
