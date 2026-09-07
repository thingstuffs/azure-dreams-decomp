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

/* Selects a town entry and writes its root-relative coordinates to the output. */
void func_800A00E8(s32 entryIndex) {
    TownRoot *root = D_80100900[0];
    TownEntry *entry;
    TownEntry *entries;
    register TownOutput *output ASM_REG("$5");   /* MATCH pin: load-bearing for the whole function shape */
    TownEntryOwner *owner;
    u16 rootX;
    u16 rootY;
    register u16 entryX ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register u16 entryY ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    u32 entryOffsetOrAddress;
    register u32 outputThirdWord ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    register s32 selectedEntryIndex ASM_REG("$2") = entryIndex;   /* MATCH pin: keeps a constant in a register as retail does */

    D_80100B68[0] = selectedEntryIndex;

    entryOffsetOrAddress = selectedEntryIndex * sizeof(TownEntry);
    do {
        owner = root->owner;
    } while (0);
    rootX = root->x;
    rootY = root->y;
    entries = owner->entries;
    ASM_KEEP(selectedEntryIndex);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(root);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    D_80100B50.first.word = 0;
#ifdef NON_MATCHING
    entry = (TownEntry *)((u8 *)entries + entryOffsetOrAddress);
#else
    do {
        entryOffsetOrAddress += (u32)entries;
        entry = (TownEntry *)entryOffsetOrAddress;
    } while (0);
#endif
    entryX = entry->x;
    output = &D_80100B50;
    output->second.word = 0;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    output->first.half.y = entryX + rootX;
    entryY = entry->y;
    outputThirdWord = 0xFFE00000;
    output->third = outputThirdWord;
    output->second.half.y = entryY + rootY;
}
