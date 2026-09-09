#include "common.h"

typedef struct TownAllocEntry {
    s8 kind;
    s8 state;
    s16 value;
    s32 size;
} TownAllocEntry;

extern s32 D_800CF720[];
extern s32 D_801131E4;

extern void func_80053CFC(u32 *, s32);
extern void func_8008AC84(s32);
extern s32 func_8008ACE8(s32);
extern void func_8008AD90(s32, s32);
extern u32 *func_8008AF2C(s32, s32, s32);

/* Make room for an allocation, record its metadata, and transfer its data. */
s32 func_8008AFB0(s32 kind, s32 state, s32 value, s32 start_index)
{
    s32 alloc_size;
    s32 available;
    s32 index;
    u32 *allocation;
    TownAllocEntry *entry;
    TownAllocEntry *entry_base;
    s32 entry_offset;
    TownAllocEntry *table;

    index = start_index;
    allocation = func_8008AF2C(kind, state, value);
    if (allocation == 0) {
        return 0;
    }

    alloc_size = ((*allocation >> 11) + 1) << 11;
    available = 0x8000 - func_8008ACE8(index);
    if (alloc_size > 0x7FFF) {
        index = 0;
        func_8008AC84(index);
    } else if (available < alloc_size) {
        entry_base = (TownAllocEntry *)D_800CF720;
        entry_offset = index * sizeof(TownAllocEntry);
        entry = (TownAllocEntry *)(entry_offset + (s32)entry_base);
        goto loop_body;
        do {
            entry--;
            index--;
loop_body:
            available += entry->size;
            func_8008AC84(index);
        } while (available < alloc_size);
    }

    func_8008AD90(index, alloc_size);
    func_8008AC84(index + 1);
    table = (TownAllocEntry *)D_800CF720;
    table[0].kind = kind;
    table[0].state = state;
    table[0].value = value;
    table[0].size = alloc_size;
    func_80053CFC(allocation, D_801131E4);
    return 0;
}
