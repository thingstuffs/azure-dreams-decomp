#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_800814A8[3];

void func_80099FDC(void *arg0)
{
    void *temp_a1;
    void *temp_v1;
    void *owner;

    owner = D_800814A8[0];
    FIELD(arg0, s32, 0x10) = FIELD(arg0, s32, 0x10) & 0x7FFFFFFF;
    temp_v1 = (u8 *)FIELD(owner, void *, 0x58) + 0x20;
    temp_a1 = (u8 *)arg0 + 0x20;
    FIELD(temp_a1, void *, 0x5C) = FIELD(temp_v1, void *, 0x5C);
    FIELD(temp_a1, void *, 0x58) = FIELD(owner, void *, 0x58);
    FIELD(owner, void *, 0x58) = arg0;
    FIELD(temp_v1, void *, 0x5C) = arg0;
}
