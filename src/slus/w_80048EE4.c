#include "common.h"

/* Fixed 0x104-byte allocator (matched at gcc 2.8.1, defined in src/code7.c);
   only the size arg is set explicitly by callers of this shape. */
extern void *func_8004B404(s32 a0);

extern void func_8004CC38(void **a0, s32 a1);

/* Allocates and initializes a fixed-size pool of pointers to paired 16-byte records. */
void *allocPointerPool(void **pool, s32 record_count)
{
    void *next_record;
    s32 record_index;

    pool = (void **)(*pool = func_8004B404(0x104));
    if (pool != 0) {
        next_record = (void *)&pool[record_count];
        for (record_index = 0; record_index < record_count; record_index++) {
            pool[record_index] = next_record;
            next_record = (void *)((char *)next_record + 0x10);
        }
        for (record_index = 0; record_index < record_count; record_index++) {
            *(void **)((char *)pool[record_index] + 4) = next_record;
            next_record = (void *)((char *)next_record + 0x10);
        }
        func_8004CC38(pool, record_count);
    }
    return pool;
}
