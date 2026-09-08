#include "common.h"

extern s32 D_800D66E8[3];
extern s32 D_800D66F0[3];
extern s32 D_800D6718[3];
extern s32 D_800D671C[3];
extern void func_800C3050(void *, s32, void *, void *, void *, void *);

/* Initialize the object with resource 0x4A and set its state to 1. */
void func_800CAA8C(void *object, s32 unused, s16 *state) {
    func_800C3050(object, 0x4A, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    state[9] = 1;
}
