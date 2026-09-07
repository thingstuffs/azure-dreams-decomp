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

/* Selects an available option and triggers its associated action, or returns -1. */
s32 func_80016C7C(void)
{
    s32 available[4];
    s32 choice;

    choice = 0;
    available[0] = 0;
    available[1] = 0;
    available[2] = 0;
    available[3] = 0;

    if (func_80018640(0x1472) != 0) {
        choice = 1;
        available[0] = 1;
    }
    if (func_80018640(0x1470) != 0) {
        choice += 1;
        available[1] = 1;
    }
    if (func_80018640(0x1474) != 0) {
        choice += 1;
        available[2] = 1;
    }
    if (func_80018640(0x146E) != 0) {
        choice += 1;
        available[3] = 1;
    }

    if (choice != 0) {
        u32 root_page = 0x80010000;

        {
            s32 *available_flags = available;

            do {
                choice = (*(TownRoot **)(root_page + 0x6000))->callbacks->select(4);
            } while (available_flags[choice] == 0);
        }
        func_80018548(choice + 0x9B7);
    } else {
        choice = -1;
    }

    return choice;
}
