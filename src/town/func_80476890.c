#include "common.h"


extern s32 D_80016530[];
extern s32 D_80019BB4;

/* Returns the table entry at the current index. */
s32 get_current_indexed_table_entry(void) {
    s32 index = D_80019BB4;
    return D_80016530[index];
}
