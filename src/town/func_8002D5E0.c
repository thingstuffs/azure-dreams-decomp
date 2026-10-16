/* Relink of matched town/func_800C82F4; every changed retail word is a paired relocation. */
#define D_800D54DC D_800D6734
#define D_800D55E8 D_800D6770
#define D_800D55F0 D_800D6778
#define D_800D5618 D_800D67A0
#define D_800D561C D_800D67A4
#include "common.h"
#include "shared/object_index_slots.h"

extern void func_800C2E84(void *state, s32 output, void *entries);
extern u8 D_800C3BF4[];
extern u8 D_800D6734[];
extern u8 D_800D6770[];
extern u8 D_800D6778[];
extern u8 D_800D67A0[];
extern u8 D_800D67A4[];

/* Initialize the object tables and clear its indexed status byte. */
void func_800CAD40(void *object, s32 unused, s32 init_value) {
    ((u8 *)D_80082660)[(*(s32 *)((u8 *)object + 0x60)) * 8] = 0;
    *(void **)((u8 *)object + 0x58) = D_800D67A0;
    *(void **)((u8 *)object + 0x5C) = D_800D67A4;
    *(void **)((u8 *)object + 0x7C) = D_800D6770;
    *(void **)((u8 *)object + 0x80) = D_800D6778;
    func_800C2E84(object, init_value, D_800D6734);
    *(void **)((u8 *)object + 0x54) = D_800C3BF4;
}
