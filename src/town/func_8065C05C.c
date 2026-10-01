#include "common.h"
#include "shared/record_ptrs.h"

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


static __inline__ S_func_8065C05C_0 *terminate_entries(S_func_8065C05C_0 *base, s32 count)
{
    u32 offset = count * 4;
    S_func_8065C05C_0 *end;
    offset += (u32)base;
    end = (S_func_8065C05C_0 *)offset;
    end->unk_01 = 0;
    end->unk_00 = 0;
    return base;
}

/* Build a terminated list of four-byte entries for IDs accepted by the callback. */
S_func_8065C05C_0 *func_8065C05C(register S_func_8065C05C_0 *entries_base) {
    s32 entry_count;
    register s32 entry_id;
    s32 entry_tag;
    S_func_8065C05C_1 *globals_page;

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

    return terminate_entries(entries_base, entry_count);
}
