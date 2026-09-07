#include "common.h"

extern void func_8004E994(s32 arg0);

void func_800240EC(void *arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        func_8004E994(*(*(s32 **)((u8*)arg0 + 0x260 + i * 4)));
        *(*(s32 **)((u8*)arg0 + 0x260 + i * 4)) = 0;
    }
    *(*(s32 **)((u8*)arg0 + 0x26C)) = 0;
}
