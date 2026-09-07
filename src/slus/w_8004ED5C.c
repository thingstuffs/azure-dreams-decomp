#include "common.h"

/* Registers an input handler (1, 0x1E, func_8004EC20) for the object; on
 * success, installs func_8004ED00 as the object's update-callback (stored
 * at offset -0x10 relative to the pointer, matching the sibling setup in
 * func_8004ED00/func_8004EDA8). */
extern s32 func_80044144(s32 a0, s32 a1, void *a2, void *a3);
extern void func_8004EC20(void *a0);
extern void func_8004ED00(void *a0);

typedef struct S_8004ED5C {
    void (*unk18)(void *);
} S_8004ED5C;

void func_8004ED5C(void *a0)
{
    void *s0 = a0;

    if (func_80044144(1, 0x1E, (void *)func_8004EC20, s0) != 0) {
        ((S_8004ED5C *)((u8 *)s0 - 0x10))->unk18 = func_8004ED00;
    }
}
