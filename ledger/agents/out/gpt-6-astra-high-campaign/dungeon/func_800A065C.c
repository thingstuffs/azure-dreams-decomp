#include "common.h"

extern void *func_8003FC64(s32);
extern s32 D_80083460;
extern s32 D_800A5D5C;

#ifdef NON_MATCHING
#define COMPILER_MEMORY_BARRIER() ((void)0)
#define COMPILER_KEEP(value) ((void)0)
#else
#define COMPILER_MEMORY_BARRIER() __asm__ __volatile__("" ::: "memory")
#define COMPILER_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#endif

/* Set the object data pointer and increment the global state counter. */
void func_800A5DBC(void) {
    void *base;

    ((s32 **)func_8003FC64(0))[4] = &D_800A5D5C;
    COMPILER_MEMORY_BARRIER();
    base = &D_80083460;
    COMPILER_KEEP(base);
    *(u16 *)((u8 *)base + 0xA) += 1;
}
