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
    register TownRoot *root ASM_REG("$4") = D_80100900[0];
    register TownEntry *entry ASM_REG("$3");
    register TownEntry *entries ASM_REG("$6");
    register TownOutput *output ASM_REG("$5");
    TownEntryOwner *owner;
    u16 rootX;
    u16 rootY;
    register u16 entryX ASM_REG("$4");
    register u16 entryY ASM_REG("$3");
    register u32 offset ASM_REG("$3");
    register u32 constant ASM_REG("$4");
    register s32 savedIndex ASM_REG("$2") = index;

    D_80100B68[0] = savedIndex;
    ASM_SCHED_BARRIER();

    offset = savedIndex * sizeof(TownEntry);
    do {
        owner = root->owner;
    } while (0);
    rootX = root->x;
    rootY = root->y;
    entries = owner->entries;
    ASM_KEEP(savedIndex);
    ASM_KEEP(root);
    ASM_KEEP(owner);

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
    ASM_SCHED_BARRIER();
    output->first.half.y = entryX + rootX;
    entryY = entry->y;
    constant = 0xFFE00000;
    output->third = constant;
    output->second.half.y = entryY + rootY;
}
