#include "common.h"

/* If arg0 is found in D_80083D08 (index looked up via func_80047BC0), set bit 0 of that entry's status field. */
typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];

extern s32 func_80047BC0(s32 arg0);

void func_80048190(s16 arg0) {
    s32 idx = func_80047BC0(arg0);

    if (idx != -1) {
        D_80083D08[idx].status = D_80083D08[idx].status | 1;
    }
}
