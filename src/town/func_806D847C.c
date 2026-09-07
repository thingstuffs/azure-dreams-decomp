#include "common.h"

typedef struct TownCallbacks {
    u8 pad0[0x54];
    s32 (*select)(u32);
} TownCallbacks;

typedef struct TownRoot {
    u8 pad0[0x20];
    TownCallbacks *callbacks;
} TownRoot;

extern TownRoot *D_80016000[4];
extern s32 func_80018640(s32);
extern void func_80018548(s32);

s32 func_80016C7C(void)
{
    s32 valid[4];
    s32 selected;

    selected = 0;
    valid[0] = 0;
    valid[1] = 0;
    valid[2] = 0;
    valid[3] = 0;

    if (func_80018640(0x1472) != 0) {
        selected = 1;
        valid[0] = 1;
    }
    if (func_80018640(0x1470) != 0) {
        selected += 1;
        valid[1] = 1;
    }
    if (func_80018640(0x1474) != 0) {
        selected += 1;
        valid[2] = 1;
    }
    if (func_80018640(0x146E) != 0) {
        selected += 1;
        valid[3] = 1;
    }

    if (selected != 0) {
        u32 page = 0x80010000;
        
        {
            s32 *valid_p = valid;

            do {
                selected = (*(TownRoot **)(page + 0x6000))->callbacks->select(4);
            } while (valid_p[selected] == 0);
        }
        func_80018548(selected + 0x9B7);
    } else {
        selected = -1;
    }

    return selected;
}

/* MECHANISM: The sibling valid[4] stack object yields the 0x30 frame and s0/s1/s2 saves.
   A guarded $s2 page carrier places the 0x8001 lui in the selected-branch delay slot.
   Its inner scope leaves valid's stack base naturally in $s1 for the callback loop. */
