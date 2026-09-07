#include "common.h"

typedef struct {
    s32 words[6];
} CopyRecord;

extern void func_800478B8(s32);
extern s32 D_800814A0;

void func_80022B80(u8 *arg0, CopyRecord *arg1, s32 arg2)
{
    CopyRecord *record;
    u16 count;

    func_800478B8(arg2);
    record = *(CopyRecord **)(arg0 + 4);
    *arg1 = *record;

    count = *(u16 *)(arg0 + 2) - 1;
    *(u16 *)(arg0 + 2) = count;
    if ((count << 16) <= 0) {
        *(u16 *)(arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
