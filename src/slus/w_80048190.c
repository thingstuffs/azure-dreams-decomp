#include "common.h"

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];

extern s32 func_80047BC0(s32 arg0);

/* Set status bit 0 for the entry matching the lookup key, if found. */
void func_80048190(s16 lookup_key) {
    s32 entry_index = func_80047BC0(lookup_key);

    if (entry_index != -1) {
        D_80083D08[entry_index].status = D_80083D08[entry_index].status | 1;
    }
}
