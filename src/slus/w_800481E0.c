#include "common.h"

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];

/* Sets bit 0 of the status field for each of the 6 entries whose flag is non-zero. */
void func_800481E0(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        S_80083D08 *p = &D_80083D08[i];
        if (p->flag) {
            p->status |= 1;
        }
    }
}
