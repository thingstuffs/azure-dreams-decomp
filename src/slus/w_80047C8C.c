#include "common.h"

extern s32 func_80047B80(void);
extern void func_80047A68(s32 a0, s32 a1);

/* Registers a value in a free slot and returns its index, or -1 if none is free. */
s32 func_80047C8C(s32 value)
{
    s32 slot = func_80047B80();

    if (slot != -1) {
        func_80047A68(slot, value);
    }
    return slot;
}
