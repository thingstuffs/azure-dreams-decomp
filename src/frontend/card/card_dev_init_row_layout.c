#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

typedef struct S_8001C738_0 {
    u8 pad_00[0x1C0];
    void * unk_1C0;
    u8 pad_1C4[0xC];
    void * unk_1D0;
    u8 pad_1D4[0xC];
    void * unk_1E0;
    u8 pad_1E4[0xC];
    void * unk_1F0;
} S_8001C738_0;

typedef struct S_8001C738_1 {
    u8 pad_00[0x4];
    s8 * unk_04;
} S_8001C738_1;

typedef struct S_8001C738_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_2;

typedef struct S_8001C738_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_3;

typedef struct S_8001C738_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001C738_4;

typedef struct S_8001C738_5 {
    u8 pad_00[0x1];
    s8 unk_01;
    s8 unk_02;
    u8 pad_03[0x5];
    s16 unk_08;
} S_8001C738_5;

typedef struct S_8001C738_6 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_6;

typedef struct S_8001C738_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_7;

typedef struct S_8001C738_8 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_8001C738_8;

/* Initializes values in four groups of four linked records. */
void card_dev_init_row_layout(void *record_groups, s32 unused_row_y, s32 unused_lower_y, s32 unused_row) {
    s32 slot_index;
    S_8001C738_0 *group_slot;

    for (slot_index = 0; slot_index < 4; slot_index++) {
        group_slot = (S_8001C738_0 *)((u8 *)record_groups + slot_index * 4);
        ((S_8001C738_5 *)(((S_8001C738_1 *)(group_slot->unk_1E0))->unk_04))->unk_08 = 0x24;
        *((S_8001C738_1 *)(group_slot->unk_1E0))->unk_04 = 0x68;
        ((S_8001C738_5 *)(((S_8001C738_1 *)(group_slot->unk_1E0))->unk_04))->unk_01 = 0x68;
        ((S_8001C738_5 *)(((S_8001C738_1 *)(group_slot->unk_1E0))->unk_04))->unk_02 = 0x60;
        ((S_8001C738_6 *)(((S_8001C738_2 *)(group_slot->unk_1C0))->unk_04))->unk_08 = 9;
        ((S_8001C738_7 *)(((S_8001C738_3 *)(group_slot->unk_1D0))->unk_04))->unk_08 = 0x42;
        ((S_8001C738_8 *)(((S_8001C738_4 *)(group_slot->unk_1F0))->unk_04))->unk_08 = 0x8F;
    }
}
