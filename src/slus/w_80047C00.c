#include "common.h"

typedef struct S_80083D08 {
    /* 0x0 */ u32 unk0;
    /* 0x4 */ u16 flags;
    /* 0x6 */ u16 unk6;
} S_80083D08;

extern S_80083D08 D_80083D08[6];
extern void bzero(void *ptr, s32 n);

/* Zeroes each 6-slot D_80083D08[] entry whose flags bit0 is set. */
void func_80047C00(void) {
    s32 i;
    S_80083D08 *p;

    i = 0;
    p = D_80083D08;
    do {
        if (p->flags & 1) {
            bzero(p, 8);
        }
        i++;
        p++;
    } while (i < 6);
}
