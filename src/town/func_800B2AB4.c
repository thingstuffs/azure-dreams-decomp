#include "common.h"

/* Global 32-bit flags word D_800814A0 (same global touched by the
 * func_8004B530 / func_8004F52C / func_8004EE90 family, see code9.c). Here
 * retail reuses a single lui-based base register for both the load and the
 * store, so declare it as a >8B struct to force gcc to materialize one
 * shared %hi/%lo address instead of the two-independent-lui -G0 shape. */
typedef struct {
    s32 val;
    s32 pad[2];
} S_800814A0;
extern S_800814A0 D_800814A0;

extern void *func_8003FC64(s32 a0);
extern s32 func_800B0198(void *a0, s32 a1);
extern s32 func_800AFE10(s32 a0);
extern s32 func_800B0158(void *a0, s32 a1);
extern void func_8004491C(void *a0, void *a1);
/* Same callback registered by func_80050EF8 via func_8004491C in this
 * overlay -- a real code symbol, not the data global m2c guessed. */
extern int func_8004CAA0(void *a0, int a1, void *a2);
/* Tail dispatcher reached via a raw retail `j` with no argument setup of its
 * own -- a0 is left holding var_s0 only because it was already resident there
 * for the preceding func_8004491C call; the C call site carries no explicit
 * argument (see docs/one_to_one_program.md R6 "$v0 hidden args" class). */
extern void func_8004B248(u16 **a0);

void *func_800B0214(s32 arg0)
{
    void *var_s0;
    void *temp_s1;

    var_s0 = func_8003FC64(0);
    temp_s1 = (void *)((u8 *)var_s0 + 0x20);
    if (var_s0 != 0) {
        if (func_800B0198(temp_s1, 0x28) != 0) {
            *(void **)((u8 *)var_s0 + 0xC) = (u8 *)var_s0 + 0xB8;
            *(s32 *)((u8 *)temp_s1 + 0xA4) = func_800AFE10(*(s32 *)((u8 *)temp_s1 + 0xA8));
            func_800B0158(temp_s1, arg0);
            func_8004491C(var_s0, (void *)func_8004CAA0);
            return var_s0;
        }
        func_8004B248((u16 **)((u8 *)var_s0 + 0xCC));
        *(u16 *)((u8 *)var_s0 + 0x1E) |= 0x8000;
        var_s0 = 0;
        D_800814A0.val |= 0x8000;
    }
    return var_s0;
}

/* MECHANISM: The seed already supplied the exact 0x20 frame and s2/s1/s0 hold set.
   Typing the tail dispatcher void and returning the held s0 value separately exposes
   LEAD-22 SHAPE-C, which moves v0=s0 into the converted tail-jump delay slot. */
