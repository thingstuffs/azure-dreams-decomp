#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_800814A8;
extern void func_800DC078(s32, u8);

void func_800DC0BC(void *arg0, s32 *arg1) {
    void **page;
    void *owner;
    u8 temp_v1;
    u8 temp_v1_2;

    page = &D_800814A8;
    owner = *page;
    temp_v1 = FIELD(owner, u8, 0x28);
    if (temp_v1 != FIELD(arg0, s32, 0x10)) {
        func_800DC078(arg1[0], FIELD(owner, u8, 0x28));
        FIELD(arg0, s32, 0x10) = FIELD(*page, u8, 0x28);
    }
    owner = *page;
    temp_v1_2 = FIELD(owner, u8, 0x29);
    if (temp_v1_2 != FIELD(arg0, s32, 0x14)) {
        func_800DC078(arg1[0] + 0xC, FIELD(owner, u8, 0x29));
        FIELD(arg0, s32, 0x14) = FIELD(*page, u8, 0x29);
    }
}
