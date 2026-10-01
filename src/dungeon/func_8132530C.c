#include "common.h"

extern void func_800A4ACC(s32);
extern s32 func_800AB1C0(void *, s32, s32, s32);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_8016B778;

/* Initializes the state fields when the availability and value checks pass. */
void func_8016CB0C(void *state, s32 unused, s32 checkInput, s32 setupInput) {
    if (func_800AB1C0(state, unused, checkInput, setupInput) != 0) {
        func_800A4ACC(setupInput);
        if ((func_800AD9B4(checkInput, setupInput) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8c) = &D_8016B778;
            *(s32 *)((u8 *)state + 0x90) = 0;
        }
    }
}
