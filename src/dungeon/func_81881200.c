#include "common.h"

typedef struct {
    u16 value;
    u8 pad[10];
} Global16;

typedef struct {
    u32 value;
    u8 pad[8];
} Global32;

extern Global16 D_800257CE;
extern Global32 D_800814A0;
extern void func_800478B8(void *);

void func_80024A00(void *arg0, s32 arg1, void *arg2)
{
    u16 flags = *(u16 *)((u8 *)arg0 + 0x1C);

    D_800257CE.value = D_800257CE.value + 1;
    if (flags & 1) {
        func_800478B8(arg2);
        if (*(u16 *)((u8 *)arg2 + 0x14) & 0x4000) {
            *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
    *(u16 *)((u8 *)arg0 + 0x1C) += 1;
}

/* MECHANISM: Cache arg0+0x1C before incrementing the global counter, removing
   the alias barrier so its halfword store fills the first branch delay slot.
   Long-lived arg0/arg2 naturally select s0/s1 and the exact 0x20-byte frame. */
