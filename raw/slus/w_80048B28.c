#include "common.h"

/* Struct for the objects pointed to by D_80083110[]: only fields at offset
 * 0x08 and 0x28 are accessed by this function/its siblings. */
typedef struct S_80083110 {
    u8 pad_00[0x08];
    s32 unk08;
    u8 pad_0C[0x28 - 0x0C];
    s32 unk28;
} S_80083110;

extern S_80083110 *D_80083110[4];

extern void func_800488F0(s32 a0, s32 a1, s32 a2);

/* Iterate over the 4 slots of D_80083110; for each occupied slot, notify
 * func_800488F0 with the slot's unk08/unk28 fields and reason=1, then clear
 * the slot. */
void func_80048B28(void)
{
    S_80083110 **p = D_80083110;
    s32 i;

    for (i = 4; i > 0; i--, p++) {
        S_80083110 *cur = *p;
        if (cur != 0) {
            func_800488F0(cur->unk08, cur->unk28, 1);
            *p = 0;
        }
    }
}
