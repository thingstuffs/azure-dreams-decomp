#include "common.h"

extern u8 D_800136B8;
extern void *D_800718E4[];
extern u8 D_80082E78;
extern u8 D_800D1A0C[];
extern u8 D_800D1D1C[];
extern u8 D_800D1D24[];
extern u8 D_800D1D2C[];
extern u8 D_800D1D54[];
extern u8 D_800D1D5C[];
extern u8 D_800D1D64[];
extern u8 D_800D1D6C[];
extern u8 D_800D1DB4[];
extern u8 D_800D1DBC[];
extern u8 D_800D1DC4[];
extern u8 D_800D1DCC[];
extern u8 D_800D1DD4[];
extern u8 D_800D1DDC[];
extern u8 D_800D1DE4[];
extern u8 D_800D1DEC[];
extern u8 D_800D1E7C[];
extern u8 D_800D2FB4[];
extern u8 D_800D3814[];

/* Builds a null-terminated entry list for the current map kind and variant. */
void func_800B94FC(void) {
    s32 entry_count;
    register s32 choice_index ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 map_kind;
    s32 variant;
    register s32 selector ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void **entries;
    register void **entry_slot ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    void *entry;
    u8 *map_records;
    u8 *fallback_records;
    u8 *town_state;
    u8 *choices;
    void **next_entry;
    void **entries_base;

    entry_count = 1;
    D_800718E4[0] = D_800D1D1C;
    if ((u32)(D_80082E78 - 0x16) >= 2U) {
        entry_count = 3;
        D_800718E4[1] = D_800D1D24;
        D_800718E4[2] = D_800D1D2C;
    }
    entries = D_800718E4;

    map_records = D_800D2FB4;
    map_kind = map_records[D_800D3814[6] << 5];
    selector = 0xF;
    if (map_kind == selector) {
        goto kind_15_prep;
    }
    selector = ((s32)map_kind < 0x10);
    if (selector) {
        selector = 5;
        if (map_kind == selector) {
            goto kind_5_prep;
        }
        choice_index = 0;
        goto fallback;
    }
    selector = 0x10;
    if (map_kind == selector) {
        goto kind_16_prep;
    }
    choice_index = 0;
    goto fallback;

kind_5_prep:
    selector = 0xC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
kind_5:
    variant = D_800136B8;
    if (variant == selector) {
        goto kind_5_12;
    }
    if ((s32)variant < 0xD) {
        if (variant == 0xB) {
            goto kind_5_11;
        }
        goto kind_5_default;
    }
    if (variant == 0xD) {
        goto kind_5_13;
    }

kind_5_default:
    entries_base = D_800718E4;
    ASM_KEEP(entry_count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_slot = &entries_base[entry_count];
    entry = D_800D1D54;
    goto store_value;

kind_5_11:
    entry_slot = &entries[entry_count];
    entry = D_800D1D5C;
    goto store_value;

kind_5_12:
    entry_slot = &entries[entry_count];
    entry = D_800D1D64;
    goto store_value;

kind_5_13:
    entry_slot = &entries[entry_count];
    entry = D_800D1D6C;
    goto store_value;

kind_15_prep:
    ASM_UNDEF(selector);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
kind_15:
    variant = D_800136B8;
    ASM_KEEP(selector);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    if (variant == 0xC) {
        goto kind_15_12;
    }
    if ((s32)variant < 0xD) {
        if (variant == 0xB) {
            goto kind_15_11;
        }
        goto kind_15_default;
    }
    if (variant == 0xD) {
        goto kind_15_13;
    }

kind_15_default:
    entries_base = D_800718E4;
    ASM_KEEP(entry_count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_slot = &entries_base[entry_count];
    entry = D_800D1DB4;
    goto store_value;

kind_15_11:
    entry_slot = &entries[entry_count];
    entry = D_800D1DBC;
    goto store_value;

kind_15_12:
    entry_slot = &entries[entry_count];
    entry = D_800D1DC4;
    goto store_value;

kind_15_13:
    entry_slot = &entries[entry_count];
    entry = D_800D1DCC;
    goto store_value;

kind_16_prep:
    selector = 0xC;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
kind_16:
    variant = D_800136B8;
    if (variant == selector) {
        goto kind_16_12;
    }
    if ((s32)variant < 0xD) {
        if (variant == 0xB) {
            goto kind_16_11;
        }
        goto kind_16_default;
    }
    if (variant == 0xD) {
        goto kind_16_13;
    }

kind_16_default:
    entries_base = D_800718E4;
    ASM_KEEP(entry_count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_slot = &entries_base[entry_count];
    entry = D_800D1DD4;
    goto store_value;

kind_16_11:
    entry_slot = &entries[entry_count];
    entry = D_800D1DDC;
    goto store_value;

kind_16_12:
    entry_slot = &entries[entry_count];
    entry = D_800D1DE4;
    goto store_value;

kind_16_13:
    entry_slot = &entries[entry_count];
    entry = D_800D1DEC;

store_value:
    *entry_slot = entry;
    ASM_KEEP(entry);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    entry_count++;
    entries_base = D_800718E4;
    entry_slot = &entries_base[entry_count];
    entry = D_800D1E7C;
    *entry_slot = entry;
    ASM_KEEP(entry_slot);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_count++;
    goto finish;

fallback:
    fallback_records = D_800D2FB4;
    town_state = D_800D3814;
    choices = D_800D1A0C;
    entries_base = D_800718E4;
    entry_slot = (void **)(entry_count << 2);
    next_entry = (void **)((unsigned long)entry_slot + (unsigned long)entries_base);
    do {
        selector = town_state[6];
        entry_count++;
        entry_slot = (void **)(u32)*(u8 *)(((unsigned long)selector << 5) + (unsigned long)fallback_records);
        selector = choice_index << 2;
        entry_slot = (void **)(((unsigned long)(s32)entry_slot << 3) + (unsigned long)choices);
        entry = *(void **)((unsigned long)selector + (unsigned long)entry_slot);
        *next_entry = entry;
        choice_index++;
        next_entry++;
    } while (choice_index < 2);

finish:
    ASM_KEEP(entry_count);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    entry_slot = D_800718E4;
    selector = entry_count << 2;
    *(void **)((unsigned long)selector + (unsigned long)entry_slot) = 0;
}
