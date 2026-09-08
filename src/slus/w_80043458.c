#include "common.h"

#include "common.h"

typedef struct {
    u8 pad[0x24B];
    u8 value;
} BytePage;

typedef struct {
    u8 pad[0x304];
    s32 flags;
} WordPage;

typedef struct {
    u8 pad[0xA94];
    s32 flags;
} SecondPage;

/* Reset global state and clear flags in the primary and secondary entry arrays. */
void func_80043458(void) {
    s32 entry_count;
    s32 primary_mask;
    volatile WordPage *primary_flags;
    volatile BytePage *entry_bytes;
    volatile u8 *state_base;
    s32 secondary_mask;
    volatile SecondPage *secondary_flags;

    entry_count = 0;
    primary_mask = ~0x4000;
    ASM_USE(primary_mask);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    primary_flags = (WordPage *)0x80010000;
    entry_bytes = (BytePage *)primary_flags;
    ASM_KEEP(entry_bytes);   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
    state_base = (u8 *)entry_bytes;
    ASM_KEEP(state_base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    *(volatile s32 *)(state_base + 0x208C) = 0;
    *(volatile s32 *)(state_base + 0x2090) = 0;
    state_base[0x2D52] = 0xFF;
    state_base[0x2D53] = 0xFF;
    state_base[0x21E0] = 0xFF;
    state_base[0x21E1] = 0xFF;
    do {
        entry_count += 1;
        entry_bytes->value &= 0x5F;
        primary_flags->flags &= primary_mask;
        entry_bytes = (BytePage *)((u8 *)entry_bytes + 4);
        primary_flags = (WordPage *)((u8 *)primary_flags + 0x54);
    } while (entry_count < 0x14);

    entry_count = 0;
    secondary_mask = ~0x4000;
    secondary_flags = (SecondPage *)0x80010000;
    do {
        entry_count += 1;
        secondary_flags->flags &= secondary_mask;
        secondary_flags = (SecondPage *)((u8 *)secondary_flags + 0x54);
    } while (entry_count < 0x40);
}
