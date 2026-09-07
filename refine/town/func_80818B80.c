#include "common.h"

typedef struct {
    s32 words[6];
} CopyRecord;

extern void func_800478B8(s32);
extern s32 D_800814A0;

/* Copies an entry's record, decrements its count, and flags exhaustion. */
void func_80022B80(u8 *entry, CopyRecord *out_record, s32 update_arg)
{
    CopyRecord *source_record;
    u16 remaining;

    func_800478B8(update_arg);
    source_record = *(CopyRecord **)(entry + 4);
    *out_record = *source_record;

    remaining = *(u16 *)(entry + 2) - 1;
    *(u16 *)(entry + 2) = remaining;
    if ((remaining << 16) <= 0) {
        *(u16 *)(entry - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
