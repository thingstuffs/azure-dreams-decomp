#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x2D70];
    s32 words[0x800];
} MemoryPage;

void func_80033AE8(s32 arg0) {
    u32 value = arg0;
    u32 index = value & 0xFFFF;
    u32 one = 1;

    if (index == 0) {
        return;
    }
    if (index == one) {
        return;
    }
    ((volatile MemoryPage *)0x80010000)->words[index >> 5] &=
        ~(one << (value & 0x1F));
}
