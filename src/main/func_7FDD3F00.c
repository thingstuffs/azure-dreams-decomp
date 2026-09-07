#include "common.h"

extern s32 *func_7003FC64(s32);
extern void func_7004491C(s32 *, void *);
/* >8B so address-of uses %hi/%lo (not $gp) */
extern s32 D_80053858[4];

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} Blk16;

void func_7FDD3F00(s32 arg0, void *arg1) {
    s32 *temp_v0;
    Blk16 *dst;
    Blk16 *src;
    Blk16 *end;

    temp_v0 = func_7003FC64(1);
    dst = (Blk16 *)(temp_v0 + 8); /* +0x20 bytes */
    if (temp_v0 != 0) {
        src = (Blk16 *)arg1;
        end = src + 3; /* 0x30 bytes */
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        temp_v0[4] = arg0;
        func_7004491C(temp_v0, &D_80053858);
    }
}
