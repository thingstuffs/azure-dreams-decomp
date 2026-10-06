#include "common.h"

typedef struct S_80123604_0 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_80123604_0;   /* *dst in func_80123604 */

typedef struct S_80123604_1 {
    u8 pad_00[0x68];
    void * unk_68;
    void * unk_6C;
} S_80123604_1;   /* tail_dst in func_80123604 */

typedef struct S_80123604_2 {
    u8 pad_00[0x64];
    u16 unk_64;
    u16 unk_66;
    u8 pad_68[0x4];
    u16 unk_6C;
    u16 unk_6E;
} S_80123604_2;   /* tail_src in func_80123604 */

typedef struct S_80123604_3 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
} S_80123604_3;   /* ((S_80123604_0 *)(*dst))->unk_04 in func_80123604 */

typedef struct S_80123604_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_80123604_4;   /* ((S_80123604_0 *)(*dst))->unk_08 in func_80123604 */

typedef struct S_80123604_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123604_5;   /* ((S_80123604_1 *)tail_dst)->unk_68 in func_80123604 */

typedef struct S_80123604_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80123604_6;   /* ((S_80123604_1 *)tail_dst)->unk_6C in func_80123604 */

typedef struct S_80123604_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_80123604_7;   /* ((S_80123604_5 *)(((S_80123604_1 *)tail_dst)->unk_68))->unk_08 in func_80123604 */

typedef struct S_80123604_8 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_80123604_8;   /* ((S_80123604_6 *)(((S_80123604_1 *)tail_dst)->unk_6C))->unk_08 in func_80123604 */



extern u8 D_80126A18[0x70];
extern u8 D_80129728[0x38];

typedef struct SourceEntry {
    s32 word;
    u16 first;
    u16 second;
} SourceEntry;

/* Initializes fourteen objects from the source table and overrides the last two value pairs. */
void func_80123604(void) {
    {
        SourceEntry *source_entry;
        u8 *address_base;
        void **object_slot;
        s32 entry_index = 0;
        s16 default_first = 0x10;
        s16 default_second = 0xE0;

        address_base = (u8 *)&D_80129728;
        object_slot = (void **)(address_base + 0x38);
        source_entry = (SourceEntry *)D_80126A18;
        do {
            ((S_80123604_0 *)(object_slot[entry_index]))->unk_00 = 0;
            ((S_80123604_3 *)(((S_80123604_0 *)(object_slot[entry_index]))->unk_04))->unk_08 = source_entry[entry_index].first;
            ((S_80123604_3 *)(((S_80123604_0 *)(object_slot[entry_index]))->unk_04))->unk_0A = source_entry[entry_index].second;
            ((S_80123604_4 *)(((S_80123604_0 *)(object_slot[entry_index]))->unk_08))->unk_06 = default_first;
            ((S_80123604_4 *)(((S_80123604_0 *)(object_slot[entry_index]))->unk_08))->unk_08 = default_second;
            entry_index++;
        } while (entry_index < 0xE);
    }

    {
        u8 *source_table;
        u8 *object_table;

        object_table = (u8 *)&D_80129728;
        source_table = (u8 *)&D_80126A18;
        ((S_80123604_7 *)(((S_80123604_5 *)(((S_80123604_1 *)object_table)->unk_68))->unk_08))->unk_06 =
            ((S_80123604_2 *)source_table)->unk_64;
        ((S_80123604_7 *)(((S_80123604_5 *)(((S_80123604_1 *)object_table)->unk_68))->unk_08))->unk_08 =
            ((S_80123604_2 *)source_table)->unk_66;
        ((S_80123604_8 *)(((S_80123604_6 *)(((S_80123604_1 *)object_table)->unk_6C))->unk_08))->unk_06 =
            ((S_80123604_2 *)source_table)->unk_6C;
        ((S_80123604_8 *)(((S_80123604_6 *)(((S_80123604_1 *)object_table)->unk_6C))->unk_08))->unk_08 =
            ((S_80123604_2 *)source_table)->unk_6E;
    }
}
