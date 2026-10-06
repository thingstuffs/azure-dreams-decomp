#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

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

extern u8 D_80016034[];
extern u8 D_8001605C[];
extern void *func_80018F20(void **slots);

/* Copies a four-byte entry, clears its flag bits, and appends it to the object list. */
void func_800190C0(const Copy4 *input)
{
    void **slot;
    Copy4 *entry;

    slot = D_80016000->unk_38->entries;
    entry = func_80018F20(slot);
    if (entry == 0) {
        ((TownService *)D_80016000->unk_20)->report(D_80016034, D_8001605C, 0x80);
        ((TownService *)D_80016000->unk_20)->fatal(1);
    }
    *entry = *input;
    entry->bytes[3] &= 0x5F;
    while (*slot != 0)
        slot++;
    slot[0] = entry;
    slot[1] = 0;
}
