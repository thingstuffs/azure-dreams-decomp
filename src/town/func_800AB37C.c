#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

typedef struct {
    Vec3 first;
    Vec3 second;
} Pair;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused_0C;
    s32 unused_10;
} Work;

extern s32 func_800374F4();
extern void func_80097AD0();
extern void func_800A895C();
extern Pair D_80089128;
extern void *memcpy();

void func_800A8ADC(s32 arg0, s32 *arg1) {
    Pair local;
    Work work;
    u8 *page;
    Pair *source;
    s32 x;
    s32 z;
    register s32 y ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *shared = arg1;
    void *old_arg;

#ifdef NON_MATCHING
    page = (u8 *)&D_80089128 + 0x6ED8;
#else
    page = (u8 *)0x80090000;
#endif
    ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    source = (Pair *)(page - 0x6ED8);
    ASM_KEEP_NV(source);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    memcpy(&local.first, &source->first, sizeof(Vec3));
    x = source->second.x;
    ASM_USE2_NV(page, x);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    y = source->second.y;
    z = source->second.z;
    local.second.x = x;
    local.second.y = y;
    local.second.z = z;
    ASM_USE_NV(y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_USE_NV(shared);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    work.x = ((s32 *)shared)[0];
    work.y = ((s32 *)shared)[1];
    work.z = ((s32 *)shared)[2] + 0x100000;
    x = func_800374F4(2, z, source);
    old_arg = shared;
    shared = &local;
    func_800A895C(old_arg, shared, (x & 0xFFFF) + 2);
    func_80097AD0(&work, shared, (func_800374F4(2) & 0xFFFF) + 2);
}
