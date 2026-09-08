#include "common.h"

typedef void (*TownCall3)(void *, void *, s32);
#ifndef NON_MATCHING
typedef void TownFatal1(s32) __attribute__((noreturn));
#endif
typedef struct Copy4 {
    u8 bytes[4];
} Copy4;
typedef struct TownService {
    u8 pad_000[0x168];
    TownCall3 report;
    u8 pad_16C[8];
#ifdef NON_MATCHING
    void (*fatal)(s32) __attribute__((noreturn));
#else
    TownFatal1 *fatal;
#endif
} TownService;
typedef struct TownSlotList {
    void *entries[256];
} TownSlotList;
typedef struct TownObjectBase {
    u8 pad_000[0x29C];
    TownSlotList list;
} TownObjectBase;
typedef struct TownRoot {
    u8 pad_00[0x20];
    TownService *service;
    u8 pad_24[0x14];
    TownObjectBase *object_base;
} TownRoot;
typedef struct TownArena {
    u8 pad_0000[0x6000];
    TownRoot *root;
} TownArena;

extern u8 D_80016034[16];
extern u8 D_8001605C[];
extern void *func_80018F20(void **slots);

/* Copies a four-byte entry, clears its flag bits, and appends it to the object list. */
void func_800190C0(const Copy4 *input)
{
    u8 first_byte = input->bytes[0];
    const Copy4 *source;
    TownArena *arena;
    void **slot;
    Copy4 *entry;

    if (first_byte != 0)
        source = input;
    else
        source = (const Copy4 *)((const u8 *)input + first_byte);
    arena = (TownArena *)(unsigned long)
        (0x80010000U | (source->bytes[0] ^ source->bytes[0]));
    if (first_byte != 0) {
        TownRoot *initial_root = arena->root;
        slot = initial_root->object_base->list.entries;
    } else {
        TownRoot *initial_root = arena->root;
        slot = (void **)((u8 *)initial_root->object_base + 0x29C);
    }
    entry = func_80018F20(slot);
    if (entry == 0) {
        u8 *report_base = (u8 *)(unsigned long)0x80010000U;
        u8 *report_data;
        TownRoot *report_root = arena->root;
        TownCall3 report = report_root->service->report;
        TownRoot *fatal_root;

        ASM_KEEP_NV(report_base);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (report != 0)
            report_data = report_base + 0x6034;
        else
            report_data = report_base + 0x6034 + (report != 0);
        report(report_data, D_8001605C, 0x80);
        fatal_root = arena->root;
        fatal_root->service->fatal(1);
    }
    *entry = *source;
    entry->bytes[3] &= 0x5F;
    while (*slot != 0)
        slot++;
    slot[0] = entry;
    slot[1] = 0;
}
