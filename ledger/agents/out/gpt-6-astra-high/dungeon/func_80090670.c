#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 unk0C;
    u8 pad1[0x14 - 0x10];
    u16 unk14;
} D_80083460_t;

extern D_80083460_t D_80083460;

/* Set object state 0x15, clear two fields, and update the shared value and counter. */
void func_80095DD0(void *object, s32 unused_1, s32 unused_2, s32 shared_value) {
    *((u8 *)object + 0x9A) = 0x15;
    *((u8 *)object + 0x9B) = 0;
    *(s32 *)((u8 *)object + 0x8C) = 0;
    D_80083460.unk0C = shared_value;
    D_80083460.unk14++;
}
