#include "common.h"

typedef struct S_func_8065C05C_0 {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
} S_func_8065C05C_0;

typedef struct S_func_8065C05C_1 {
    u8 pad_00[0x6000];
    void *unk_6000;
} S_func_8065C05C_1;

typedef struct S_func_8065C05C_2 {
    u8 pad_00[0x20];
    void *unk_20;
} S_func_8065C05C_2;

typedef struct S_func_8065C05C_3 {
    u8 pad_00[0x70];
    s32 (*unk_70)(s32);
} S_func_8065C05C_3;

extern u8 D_80016000[12];

/* Build a terminated list of four-byte entries for IDs accepted by the callback. */
void func_8065C05C(void *entries) {
    register S_func_8065C05C_0 *entries_base;
    s32 entry_count;
    register s32 entry_id;
    register s32 entry_tag ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register S_func_8065C05C_1 *globals_page ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register S_func_8065C05C_0 *entries_copy ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 terminator;

    entries_base = entries;
    entry_count = 0;
    entry_id = 0;
    globals_page = (S_func_8065C05C_1 *)0x80010000;
    entry_tag = 0x17;
    do {
        if (((S_func_8065C05C_3 *)((S_func_8065C05C_2 *)globals_page->unk_6000)->unk_20)->unk_70(entry_id) != 0) {
            entries_base[entry_count].unk_00 = entry_id;
            entries_base[entry_count].unk_01 = entry_tag;
            entries_base[entry_count].unk_03 = 0;
            entries_base[entry_count].unk_02 = 0;
            entry_count += 1;
        }
        entry_id += 1;
    } while (entry_id < 0x43);

    entries_copy = entries_base;
    terminator = entry_count;
    terminator <<= 2;
    terminator += (u32)entries_copy;
    ((S_func_8065C05C_0 *)terminator)->unk_01 = 0;
    ((S_func_8065C05C_0 *)terminator)->unk_00 = 0;
    ASM_USE2(entries_copy, terminator);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
}
