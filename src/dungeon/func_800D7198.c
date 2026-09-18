#include "common.h"

typedef void (*Func)(void *, s32);
typedef void (*FinalFunc)(void *);

extern Func D_800E2934[];
extern void func_800DC724(void *);

/* Runs callbacks for slots 1 through 7, then processes the object and its final callback. */
void func_800DC8F8(u8 *object) {
    s32 slot;
    FinalFunc final_callback;

    for (slot = 1; slot < 8; slot++) {
        D_800E2934[slot](object, *(s32 *)(object + 0x3C) + slot * 0x10);
    }
    func_800DC724(object);
    final_callback = *(FinalFunc *)(object + 0x4C);
    if (final_callback != 0) {
        final_callback(object);
    }
}
