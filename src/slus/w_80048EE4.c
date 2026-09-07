#include "common.h"

/* Allocates a fixed 0x104-byte block, stores it through *a0, and carves it into:
   - a leading array of `a1` record-pointers (the block's own start),
   - followed by `a1` 16-byte records that the pointer array points into,
   - followed immediately by `a1` more 16-byte records whose addresses are
     written into each first record's offset-4 field.
   Then calls func_8004CC38(pool, a1) and returns the pool pointer (or NULL). */
/* Fixed 0x104-byte allocator (matched at gcc 2.8.1, defined in src/code7.c);
   only the size arg is set explicitly by callers of this shape. */
extern void *func_8004B404(s32 a0);

extern void func_8004CC38(void **a0, s32 a1);

void *allocPointerPool(void **a0, s32 a1)
{
    void *rec;
    s32 i;

    a0 = (void **)(*a0 = func_8004B404(0x104));
    if (a0 != 0) {
        rec = (void *)&a0[a1];
        for (i = 0; i < a1; i++) {
            a0[i] = rec;
            rec = (void *)((char *)rec + 0x10);
        }
        for (i = 0; i < a1; i++) {
            *(void **)((char *)a0[i] + 4) = rec;
            rec = (void *)((char *)rec + 0x10);
        }
        func_8004CC38(a0, a1);
    }
    return a0;
}
