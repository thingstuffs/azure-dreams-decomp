#include "common.h"

typedef struct TownEntry {
    u8 pad0[0x10];
    u16 x;
    u16 y;
} TownEntry;

typedef struct TownEntryOwner {
    u32 pad0;
    TownEntry *entries;
} TownEntryOwner;

typedef struct TownRoot {
    u16 x;
    u16 y;
    u8 pad4[8];
    TownEntryOwner *owner;
} TownRoot;

typedef union TownOutputWord {
    u32 word;
    struct {
        u16 x;
        u16 y;
    } half;
} TownOutputWord;

typedef struct TownOutput {
    TownOutputWord first;
    TownOutputWord second;
    u32 third;
} TownOutput;

extern TownRoot *D_80100900[];
extern TownOutput D_80100B50;
extern s32 D_80100B68[];

void func_800A00E8(s32 index) {
    TownRoot *root = D_80100900[0];
    TownEntry *entry;
    TownEntry *entries;
    register TownOutput *output ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    TownEntryOwner *owner;
    u16 rootX;
    u16 rootY;
    register u16 entryX ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u16 entryY ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u32 offset;
    register u32 constant ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 savedIndex ASM_REG("$2") = index;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

    D_80100B68[0] = savedIndex;

    offset = savedIndex * sizeof(TownEntry);
    do {
        owner = root->owner;
    } while (0);
    rootX = root->x;
    rootY = root->y;
    entries = owner->entries;
    ASM_KEEP(savedIndex);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(root);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    D_80100B50.first.word = 0;
#ifdef NON_MATCHING
    entry = (TownEntry *)((u8 *)entries + offset);
#else
    do {
        offset += (u32)entries;
        entry = (TownEntry *)offset;
    } while (0);
#endif
    entryX = entry->x;
    output = &D_80100B50;
    output->second.word = 0;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    output->first.half.y = entryX + rootX;
    entryY = entry->y;
    constant = 0xFFE00000;
    output->third = constant;
    output->second.half.y = entryY + rootY;
}
