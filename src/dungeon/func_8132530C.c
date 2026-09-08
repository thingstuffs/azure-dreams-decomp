#include "common.h"

extern void func_800A4ACC(s32);
extern s32 func_800AB1C0(void);
extern s32 func_800AD9B4(s32, s32);
extern s32 D_8016B778;

/* Initializes the state fields when the availability and value checks pass. */
void func_8016CB0C(void *state, s32 unused, s32 checkInput, s32 setupInput) {
    register s32 savedCheckInput ASM_REG("$18") = checkInput;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if (func_800AB1C0() != 0) {
        ASM_KEEP(savedCheckInput);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        func_800A4ACC(setupInput);
        if ((func_800AD9B4(savedCheckInput, setupInput) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8c) = &D_8016B778;
            *(s32 *)((u8 *)state + 0x90) = 0;
        }
    }
}
