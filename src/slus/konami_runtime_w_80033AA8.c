#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D70];
    s32 words[0x800];
} MemoryPage;

void func_80033AA8(s32 arg0) {
    u32 value = arg0;
    u32 index = value & 0xFFFF;

    if (index == 0) {
        return;
    }
    if (index == 1) {
        return;
    }
    ((volatile MemoryPage *)0x80010000)->words[index >> 5] |=
        1U << (value & 0x1F);
}
