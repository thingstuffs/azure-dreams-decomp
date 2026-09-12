#include "common.h"

typedef struct S_801234F0_0 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_801234F0_0;   /* *dst in func_801234F0 */

typedef struct S_801234F0_1 {
    u8 pad_00[0x30];
    void * unk_30;
    void * unk_34;
} S_801234F0_1;   /* tail_dst in func_801234F0 */

typedef struct S_801234F0_2 {
    u8 pad_00[0x64];
    u16 unk_64;
    u16 unk_66;
    u8 pad_68[0x4];
    u16 unk_6C;
    u16 unk_6E;
} S_801234F0_2;   /* tail_src in func_801234F0 */

typedef struct S_801234F0_3 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
} S_801234F0_3;   /* ((S_801234F0_0 *)(*dst))->unk_04 in func_801234F0 */

typedef struct S_801234F0_4 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_801234F0_4;   /* ((S_801234F0_0 *)(*dst))->unk_08 in func_801234F0 */

typedef struct S_801234F0_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801234F0_5;   /* ((S_801234F0_1 *)tail_dst)->unk_30 in func_801234F0 */

typedef struct S_801234F0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801234F0_6;   /* ((S_801234F0_1 *)tail_dst)->unk_34 in func_801234F0 */

typedef struct S_801234F0_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_801234F0_7;   /* ((S_801234F0_5 *)(((S_801234F0_1 *)tail_dst)->unk_30))->unk_08 in func_801234F0 */

typedef struct S_801234F0_8 {
    u8 pad_00[0x6];
    u16 unk_06;
    u16 unk_08;
} S_801234F0_8;   /* ((S_801234F0_6 *)(((S_801234F0_1 *)tail_dst)->unk_34))->unk_08 in func_801234F0 */


#ifdef NON_MATCHING
#define ASM_KEEP(value) ((void)0)
#else
#define TIE_LOCAL(value) ASM_KEEP(value)
#endif

extern u8 D_80126A18[0x70];
extern u8 D_80129728[0x38];

typedef struct SourceEntry {
    s32 word;
    u16 first;
    u16 second;
} SourceEntry;

/* Initialize 14 objects from table data and override the final two field pairs. */
void func_801234F0(void) {
    {
        volatile SourceEntry *src_entry;
        void **object_slot;
        s32 entry_index = 0;
        s16 first_default = 0x10;
        s16 second_default = 0xE0;

#ifdef NON_MATCHING
        object_slot = (void **)D_80129728;
        src_entry = (volatile SourceEntry *)D_80126A18;
#else
        object_slot = (void **)(D_80129728);
        src_entry = (volatile SourceEntry *)D_80126A18;
#endif
        do {
            ((S_801234F0_0 *)(*object_slot))->unk_00 = src_entry->word;
            ((S_801234F0_3 *)(((S_801234F0_0 *)(*object_slot))->unk_04))->unk_08 = src_entry->first;
            ((S_801234F0_3 *)(((S_801234F0_0 *)(*object_slot))->unk_04))->unk_0A = src_entry->second;
            entry_index++;
            ((S_801234F0_4 *)(((S_801234F0_0 *)(*object_slot))->unk_08))->unk_06 = first_default;
            src_entry++;
            ((S_801234F0_4 *)(((S_801234F0_0 *)(*object_slot))->unk_08))->unk_08 = second_default;
            object_slot++;
        } while (entry_index < 0xE);
    }

    {
        u8 *source_table;
        register u8 *object_table ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

#ifdef NON_MATCHING
        object_table = (void **)D_80129728;
        source_table = D_80126A18;
#else
        object_table = (u8 *)0x80130000;
        ASM_KEEP(object_table);
        object_table -= 0x68D8;
        source_table = (u8 *)0x80120000;
        ASM_KEEP(source_table);
        source_table += 0x6A18;
#endif
        ((S_801234F0_7 *)(((S_801234F0_5 *)(((S_801234F0_1 *)object_table)->unk_30))->unk_08))->unk_06 =
            ((S_801234F0_2 *)source_table)->unk_64;
        ((S_801234F0_7 *)(((S_801234F0_5 *)(((S_801234F0_1 *)object_table)->unk_30))->unk_08))->unk_08 =
            ((S_801234F0_2 *)source_table)->unk_66;
        ((S_801234F0_8 *)(((S_801234F0_6 *)(((S_801234F0_1 *)object_table)->unk_34))->unk_08))->unk_06 =
            ((S_801234F0_2 *)source_table)->unk_6C;
        ((S_801234F0_8 *)(((S_801234F0_6 *)(((S_801234F0_1 *)object_table)->unk_34))->unk_08))->unk_08 =
            ((S_801234F0_2 *)source_table)->unk_6E;
    }
}
