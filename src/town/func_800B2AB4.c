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
extern void func_8004B248(u16 **a0);

/* Allocate and initialize an object, register its callback, and flag initialization failure. */
void *func_800B0214(s32 init_value)
{
    void *object;
    void *object_data;

    object = func_8003FC64(0);
    object_data = (void *)((u8 *)object + 0x20);
    if (object != 0) {
        if (func_800B0198(object_data, 0x28) != 0) {
            *(void **)((u8 *)object + 0xC) = (u8 *)object + 0xB8;
            *(s32 *)((u8 *)object_data + 0xA4) = func_800AFE10(*(s32 *)((u8 *)object_data + 0xA8));
            func_800B0158(object_data, init_value);
            func_8004491C(object, (void *)func_8004CAA0);
            return object;
        }
        func_8004B248((u16 **)((u8 *)object + 0xCC));
        *(u16 *)((u8 *)object + 0x1E) |= 0x8000;
        object = 0;
        D_800814A0.val |= 0x8000;
    }
    return object;
}

