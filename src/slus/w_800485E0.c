#include "common.h"

/* Looks up a slot pointer from a Q-table (arr[a1+1] if a1+1 is in range, else
 * a fallback pointer), decrements it by 8 to reach the enclosing Result
 * record, fills unk2=1 and unk4=arr2[a2]+(a3<<3), returns the record pointer. */
typedef struct S_800485E0_Q {
    s32 *unk0;
    s32  unk4;
    s32  unk8;
} S_800485E0_Q;

typedef struct S_800485E0_Obj {
    u8 pad00[0x28];
    S_800485E0_Q **unk28;
} S_800485E0_Obj;

void *func_800485E0(S_800485E0_Obj *a0, s16 a1, s16 a2, s16 a3)
{
    S_800485E0_Q *q = *a0->unk28;
    s32 off;
    s32 val;

    if ((u32)(a1 + 1) < (u32)q->unk4) {
        off = q->unk0[a1 + 1];
    } else {
        off = q->unk8;
    }

    off = off - 8;
    val = (*a0->unk28)->unk0[a2];
    *(u16 *)(off + 2) = 1;
    *(s32 *)(off + 4) = val + (a3 << 3);
    return (void *)off;
}
