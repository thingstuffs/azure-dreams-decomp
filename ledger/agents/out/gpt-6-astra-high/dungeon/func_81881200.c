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

/* Advances counters and conditionally processes the target, propagating its status flag. */
void func_80024A00(void *record, s32 unused, void *target)
{
    u16 flags = *(u16 *)((u8 *)record + 0x1C);

    D_800257CE.value = D_800257CE.value + 1;
    if (flags & 1) {
        func_800478B8(target);
        if (*(u16 *)((u8 *)target + 0x14) & 0x4000) {
            *(u16 *)((u8 *)record - 2) |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
    *(u16 *)((u8 *)record + 0x1C) += 1;
}
