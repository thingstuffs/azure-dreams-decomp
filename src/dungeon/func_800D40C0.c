#include "common.h"

extern void func_8003DB94(void *arg0, s32 arg1, s32 arg2);
extern s16 D_80083228;
extern u8 D_800E260C[];

// Initialize object state and apply a table entry selected by the adjusted heading.
void func_800D9820(void *object, void *unusedContext, void *tableTarget, void *headingSource) {
    s32 tableByteOffset;

    *((u8 *)object + 0x9A) = 0x10;
    *((u8 *)object + 0x9B) = 0;
    *(u8 **)((u8 *)tableTarget + 0x2C) = D_800E260C;
    tableByteOffset = ((D_80083228 + *(s16 *)((u8 *)headingSource + 0x2A) + 0x100) >> 7) & 0x1C;
    func_8003DB94(tableTarget, *(s32 *)(D_800E260C + tableByteOffset), 0);
}
