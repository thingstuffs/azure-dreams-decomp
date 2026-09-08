#include "common.h"

typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct S_8002E5E8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_80010A78_a1;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_80010A78_a2;

typedef struct {
    s32 unk0;
    S_80010A78_a1 *unk4;
    S_80010A78_a2 *unk8;
} S_80010A78_a0;

/* Initialize and link two template blocks, applying defaults and a slot-based offset. */
void func_80023A78(S_80010A78_a0 *entity, S_8002E5D8 *primary, S_80010A78_a2 *secondary, s32 slot_index) {
    S_8002E5D8 *primary_template = &D_8002E5D8;
    S_8002E5E8 *secondary_template = &D_8002E5E8;
    s32 *secondary_head;

    primary->unk0 = primary_template->unk0;
    secondary_head = &secondary_template->unk0;
    primary->unk4 = primary_template->unk4;
    primary->unk8 = primary_template->unk8;
    primary->unkC = primary_template->unkC;

    ((S_8002E5E8 *)secondary)->unk0 = *secondary_head;
    ((S_8002E5E8 *)secondary)->unk4 = secondary_template->unk4;
    ((S_8002E5E8 *)secondary)->unk8 = secondary_template->unk8;

    entity->unk4 = (S_80010A78_a1 *)primary;
    entity->unk8 = secondary;
    entity->unk0 = 0;

    entity->unk4->unk8 = -0xA0;
    entity->unk4->unkA = (slot_index * 0x18) - 0x78;
    entity->unk4->unkC = 0x200;
    entity->unk4->unkF = 4;
}
