#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern volatile s32 D_80081484;
extern s32 D_800E3540;
extern void *D_800E3D7C;

void func_80094E34(void) {
    void *root;
    void *object;
    s32 saved;
    s32 flags;

    root = D_800E3D7C;
    if (FIELD(root, s32, 0x1C) & 0x100000) {
        object = FIELD(root, void *, 0x124);
        if (object != 0) {
            FIELD(object, s32, 0x1C) = (s32)(FIELD(object, s32, 0x1C) & 0xFFF7FFFF);
        }
        flags = FIELD(root, volatile s32, 0x1C);
        saved = D_80081484;
        D_80081484 = 0;
        FIELD(root, volatile s32, 0x1C) = flags & 0xFFEFFFFF;
        D_800E3540 = saved;
        
    }
}

/* MECHANISM: Frameless leaf holds the root pointer across both flag regions and pins the saved word in $a1.
   Splitting the final flag read/store gives $v0 its retail lifetime and forces the page base into $v1.
   Volatile ordering preserves root-load, saved-load, clear-store, root-store and closes the last lw swap. */
