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

void func_80022488(void *arg0) {
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    EntryT *entry;
    s32 idx;
    s32 table_index;
    s32 base;

    base = (s32)D_80030000;
    ASM_KEEP(base);   /* MATCH pin: retail immediate-load split depends on it */
    base -= 0x7f4c;
    table_index = *(s32 *)((u8 *)arg0 + 8);
    entry = (EntryT *)(table_index * 0x18 + base);
    idx = entry->count17 - 1;
    if (entry->flag14 != 0) {
        func_8002225C(entry->words[idx], *(s32 *)arg0, &sp18, &sp1C, &sp20);
        func_800223B4(arg0, sp18, sp1C, idx, sp20);
    }
}
