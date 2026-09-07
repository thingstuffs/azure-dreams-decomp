#include "common.h"

typedef struct {
    s32 words[6];
} Copy24;

extern void func_8003EA54(s32 arg0);
extern s32 D_80084D5C;

void func_8080E480(void *arg0, Copy24 *arg1, s32 arg2) {
    u16 count;
    Copy24 *src;

    func_8003EA54(arg2);
    src = *(Copy24 **)((u8 *)arg0 + 4);
    *arg1 = *src;

    count = *(u16 *)((u8 *)arg0 + 2) - 1;
    *(u16 *)((u8 *)arg0 + 2) = count;
    if ((count << 16) <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_80084D5C |= 0x8000;
    }
}
