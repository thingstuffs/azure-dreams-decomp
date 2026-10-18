/* Relink of matched dungeon/func_80A4A8E4; every changed retail word is a paired relocation. */
#define advance_randomized_motion_and_complete func_801560E4
#include "modules/dungeon_resource06_slot0.h"
extern s32 rand(void);

void func_801560E4(void *object_data, R06_801740E4_S_801740E4_0 *position, R06_801740E4_S_801740E4_2 *state) {
    s16 next_speed;
    s32 random_value;
    s32 lowered_z;

    position->unk_00 += ((dir_step_x[((R06_801740E4_S_801740E4_1 *)((u8 *)object_data
        - 0x2))->unk_16] * ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    position->unk_04 += ((dir_step_y[((R06_801740E4_S_801740E4_1 *)((u8 *)object_data
        - 0x2))->unk_16] * ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34) << 7) + (rand() & 0x7FFF);
    random_value = rand();
    lowered_z = position->unk_08 + (s32) 0xFFFE0000;
    position->unk_08 = lowered_z - (random_value & 0xFFF);
    next_speed = (u16) ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34 - 8;
    ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_34 = next_speed;
    if (((next_speed << 0x10) <= 0) || (state->unk_14 & 0x8000)) {
        ((R06_801740E4_S_801740E4_1 *)((u8 *)object_data - 0x2))->unk_00 = (u16) (((R06_801740E4_S_801740E4_1 *)((u8 *)object_data
            - 0x2))->unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
