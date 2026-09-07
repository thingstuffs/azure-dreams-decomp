#include "common.h"

/* Scans the block list at D_800799BC looking for a block whose masked start
 * value is >= arg0, or whose [start, start+size) range contains arg0.
 * Returns 1 if such a block is found (or the list is empty at that point),
 * 0 if the list is null or a terminator entry is reached first. */
typedef struct S_800799BC {
    u32 flags;
    u32 size;
} S_800799BC;

extern S_800799BC *D_800799BC[3];

s32 func_8005D95C(u32 arg0) {
    S_800799BC *entry;
    u32 v1;
    u32 maskA;
    u32 maskB;
    u32 maskC;

    if (D_800799BC[0] == 0) {
        return 0;
    }
    maskA = 0x80000000;
    maskB = 0x40000000;
    maskC = 0x0FFFFFFF;
    entry = D_800799BC[0];
    do {
        v1 = entry->flags;
        if (v1 & maskA) {
            entry++;
            continue;
        }
        if (v1 & maskB) {
            break;
        }
        v1 = v1 & maskC;
        if (v1 >= arg0) {
            return 1;
        }
        if (arg0 < v1 + entry->size) {
            return 1;
        }
        entry++;
    } while (1);
    return 0;
}
