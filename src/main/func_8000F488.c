#include "common.h"

typedef struct {
    s32 words[5];
    u8 flag14;
    u8 pad15;
    u8 pad16;
    u8 count17;
} EntryT;

extern s32 D_800280B4[3];
extern u8 D_80030000[];
__asm__(".set D_80030000, 0x80030000");

extern void func_8002225C();
extern void func_800223B4();

/* Processes the last word of an enabled table entry for the supplied object. */
void func_80022488(void *object) {
    s32 result_first;
    s32 result_second;
    s32 result_third;
    EntryT *entry;
    s32 last_index;
    s32 table_index;
    s32 table_base;

    table_base = (s32)D_80030000;
    ASM_KEEP(table_base);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    table_base -= 0x7f4c;
    table_index = *(s32 *)((u8 *)object + 8);
    entry = (EntryT *)(table_index * 0x18 + table_base);
    last_index = entry->count17 - 1;
    if (entry->flag14 != 0) {
        func_8002225C(entry->words[last_index], *(s32 *)object, &result_first, &result_second, &result_third);
        func_800223B4(object, result_first, result_second, last_index, result_third);
    }
}
