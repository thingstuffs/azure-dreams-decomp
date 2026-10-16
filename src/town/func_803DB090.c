/* Relink of matched town/func_80476890; every changed retail word is a paired relocation. */
#define townGetCurrentIndexedTableEntry func_80017890
#include "common.h"

typedef s32 M2C_UNK;

extern s32 D_80016530[];
extern s32 D_80019BB4;

/* Returns the table entry at the current index. */
s32 func_80017890(void) {
    s32 index = D_80019BB4;
    return D_80016530[index];
}
