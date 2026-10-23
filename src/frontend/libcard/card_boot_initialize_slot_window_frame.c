#include "common.h"
#include "shared/gpu_packets.h"

typedef struct S_8002E5D8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

extern S_8002E5D8 display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

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
    S_80010A78_a1 *unk4;
    DisplayPositionWords *unk8;
} S_80010A78_a0;

/* Initialize and link two template blocks, applying defaults and a slot-based offset. */
void card_boot_initialize_slot_window_frame(S_80010A78_a0 *entity, S_8002E5D8 *primary, DisplayPositionWords *secondary, s32 slot_index) {
    S_8002E5D8 *primary_template = &display_block_defaults;
    DisplayPositionWords *secondary_template = &display_vector_defaults;
    s32 *secondary_head;

    primary->unk0 = primary_template->unk0;
    secondary_head = &secondary_template->unk0;
    primary->unk4 = primary_template->unk4;
    primary->unk8 = primary_template->unk8;
    primary->unkC = primary_template->unkC;

    ((DisplayPositionWords *)secondary)->unk0 = *secondary_head;
    ((DisplayPositionWords *)secondary)->unk4 = secondary_template->unk4;
    ((DisplayPositionWords *)secondary)->unk8 = secondary_template->unk8;

    entity->unk4 = (S_80010A78_a1 *)primary;
    entity->unk8 = secondary;
    entity->unk0 = 0;

    entity->unk4->unk8 = -0xA0;
    entity->unk4->unkA = (slot_index * 0x18) - 0x78;
    entity->unk4->unkC = 0x200;
    entity->unk4->unkF = 4;
}
