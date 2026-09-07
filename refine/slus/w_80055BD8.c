#include "common.h"

#include "common.h"

typedef struct StatusBlock {
    u32 flags1;
    u32 flags2;
    u32 padding[12];
} StatusBlock;

extern StatusBlock D_800847D0;
extern void func_800553D4(s32 code);
extern void func_80055C50(s16 index);

/* Processes the selected index and sets its status flag. */
void func_80055BD8(s16 index)
{
    if ((index << 16) == 0 && (D_800847D0.flags1 & 0x100)) {
        func_800553D4(0x71);
    }
    func_80055C50(index);
    D_800847D0.flags2 |= 0x01000000 << index;
}
