#include "common.h"

extern s32 *func_7003FC64(s32);
extern void func_7004491C(s32 *, void *);
extern s32 D_80053A88;

typedef struct { s32 a, b, c, d; } Blk16;
typedef struct { s32 a, b; } Blk8;

void func_7FDD3C74(s32 arg0, void *arg1) {
    s32 *temp_v0;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *end;

    temp_v0 = func_7003FC64(1);
    if (temp_v0 != 0) {
        dst = (Blk16 *)(temp_v0 + 8);
        src = (Blk16 *)arg1;
        end = src + 2;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        *(Blk8 *)dst = *(Blk8 *)src;
        temp_v0[4] = arg0;
        func_7004491C(temp_v0, &D_80053A88);
    }
}
