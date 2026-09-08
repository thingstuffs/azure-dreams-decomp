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

/* Notify func_800488F0 with reason 1 for each occupied slot, then clear it. */
void func_80048B28(void)
{
    S_80083110 **slot = D_80083110;
    s32 slots_left;

    for (slots_left = 4; slots_left > 0; slots_left--, slot++) {
        S_80083110 *object = *slot;
        if (object != 0) {
            func_800488F0(object->unk08, object->unk28, 1);
            *slot = 0;
        }
    }
}
