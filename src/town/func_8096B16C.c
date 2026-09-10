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

/* Initializes fourteen objects from the source table and overrides the last two value pairs. */
void func_80123604(void) {
    {
        volatile SourceEntry *source_entry;
        register u8 *address_base;
        void **object_slot;
        s32 entry_index = 0;
        s16 default_first = 0x10;
        s16 default_second = 0xE0;

        ASM_KEEP(default_first);
        ASM_KEEP(default_second);
#ifdef NON_MATCHING
        object_slot = (void **)(D_80129728 + 0x38);
        source_entry = (volatile SourceEntry *)D_80126A18;
#else
        address_base = (u8 *)0x80130000;
        ASM_KEEP(address_base);
        address_base -= 0x68D8;
        ASM_KEEP(address_base);
        object_slot = (void **)(address_base + 0x38);
        address_base = (u8 *)0x80120000;
        ASM_KEEP(address_base);
        source_entry = (volatile SourceEntry *)(address_base + 0x6A18);
#endif
        do {
            ((S_80123604_0 *)(*object_slot))->unk_00 = 0;
            ((S_80123604_3 *)(((S_80123604_0 *)(*object_slot))->unk_04))->unk_08 = source_entry->first;
            ((S_80123604_3 *)(((S_80123604_0 *)(*object_slot))->unk_04))->unk_0A = source_entry->second;
            entry_index++;
            ((S_80123604_4 *)(((S_80123604_0 *)(*object_slot))->unk_08))->unk_06 = default_first;
            source_entry++;
            ((S_80123604_4 *)(((S_80123604_0 *)(*object_slot))->unk_08))->unk_08 = default_second;
            object_slot++;
        } while (entry_index < 0xE);
    }

    {
        register u8 *source_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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
