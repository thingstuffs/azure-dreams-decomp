#include "common.h"

extern s32 func_80047B80(void);
extern void func_80047A68(s32 a0, s32 a1);

/* Finds a free slot via func_80047B80(); if one is found, registers it with
 * a1 via func_80047A68(). Returns the slot index, or -1 if none free. */
s32 func_80047C8C(s32 a1)
{
    s32 slot = func_80047B80();

    if (slot != -1) {
        func_80047A68(slot, a1);
    }
    return slot;
}
