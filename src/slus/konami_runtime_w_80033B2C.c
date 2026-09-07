#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D70];
    u32 words[0x800];
} MemoryPage;

s32 func_80033B2C(s32 arg0) {
    u32 index = arg0 & 0xFFFF;
    u32 one = 1;

    if (index == 0) {
        return 0;
    }
    if (index == one) {
        return one;
    }
    return ((((volatile MemoryPage *)0x80010000)->words[index >> 5]) &
            (one << (arg0 & 0x1F))) != 0;
}
