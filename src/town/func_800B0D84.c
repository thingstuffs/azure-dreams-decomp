#include "common.h"

extern s32 D_800D156C[];

/* Returns the table entry at the given index. */
s32 townGetItemMenuTableEntry(s32 index) {
    return D_800D156C[index];
}
