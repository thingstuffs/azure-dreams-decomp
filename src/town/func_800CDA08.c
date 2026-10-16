#include "common.h"
#include "shared/object_index_slots.h"

extern void townInitializeObjectEntries(void *state, s32 output, void *entries);
extern u8 D_800CB0F0[];
extern u8 D_800D68D4[];

/* Initializes an entity, sets its state to 6, and copies its table entry's byte. */
void townInitializeEntityActionState(void *entity, s32 unused, s32 init_value) {
    townInitializeObjectEntries(entity, init_value, D_800D68D4);
    (*(u8 *)&D_80082660[*(s32 *)((u8 *)entity + 0x60)].unk_00) = 0;
    *(void **)((u8 *)entity + 0x54) = D_800CB0F0;
    *(s16 *)((u8 *)entity + 0x6C) = 6;
    *(u8 *)((u8 *)entity + 0x96) = D_80082660[*(s32 *)((u8 *)entity + 0x60)].unk_02;
}
