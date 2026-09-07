#include "common.h"

extern void *func_800374FC(s32, void *);
extern void func_8003BC18(void *, void *);
extern u8 D_801328C8[];
extern u8 D_8005860C[];

typedef struct FourWords {
    s32 word[4];
} FourWords;

void func_8080BFFC(s32 arg0, FourWords *arg1) {
    u8 *allocated;
    FourWords *src;
    FourWords *dst;
    FourWords *end;

    allocated = func_800374FC(1, D_801328C8);
    dst = (FourWords *)(allocated + 0x20);
    if (allocated != 0) {
        src = arg1;
        end = src + 3;
        do {
            *dst++ = *src++;
        } while (src != end);
        *(s32 *)(allocated + 0x10) = arg0;
        func_8003BC18(allocated, D_8005860C);
    }
}
