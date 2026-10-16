/* Relink of matched town/func_800C82F4; every changed retail word is a paired relocation. */
#define D_800D54DC D_800D675C
#define D_800D55E8 D_800D67AC
#define D_800D55F0 D_800D67B4
#define D_800D5618 D_800D67DC
#define D_800D561C D_800D67E0
#include "common.h"
#include "shared/object_index_slots.h"

extern void townInitializeObjectEntries(void *state, s32 output, void *entries);
extern u8 D_800C3BF4[];
extern u8 D_800D675C[];
extern u8 D_800D67AC[];
extern u8 D_800D67B4[];
extern u8 D_800D67DC[];
extern u8 D_800D67E0[];

/* Initialize the object tables and clear its indexed status byte. */
void func_800CACB8(void *object, s32 unused, s32 init_value) {
    ((u8 *)D_80082660)[(*(s32 *)((u8 *)object + 0x60)) * 8] = 0;
    *(void **)((u8 *)object + 0x58) = D_800D67DC;
    *(void **)((u8 *)object + 0x5C) = D_800D67E0;
    *(void **)((u8 *)object + 0x7C) = D_800D67AC;
    *(void **)((u8 *)object + 0x80) = D_800D67B4;
    townInitializeObjectEntries(object, init_value, D_800D675C);
    *(void **)((u8 *)object + 0x54) = D_800C3BF4;
}
