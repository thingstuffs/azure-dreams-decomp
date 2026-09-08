#include "common.h"

typedef struct S_800485E0_Q {
    s32 *unk0;
    s32  unk4;
    s32  unk8;
} S_800485E0_Q;

typedef struct S_800485E0_Obj {
    u8 pad00[0x28];
    S_800485E0_Q **unk28;
} S_800485E0_Obj;

/* Selects a slot or fallback, initializes its enclosing record, and returns it. */
void *func_800485E0(S_800485E0_Obj *obj, s16 slot_index, s16 base_index, s16 entry_index)
{
    S_800485E0_Q *table = *obj->unk28;
    s32 record_addr;
    s32 base_addr;

    if ((u32)(slot_index + 1) < (u32)table->unk4) {
        record_addr = table->unk0[slot_index + 1];
    } else {
        record_addr = table->unk8;
    }

    record_addr = record_addr - 8;
    base_addr = (*obj->unk28)->unk0[base_index];
    *(u16 *)(record_addr + 2) = 1;
    *(s32 *)(record_addr + 4) = base_addr + (entry_index << 3);
    return (void *)record_addr;
}
