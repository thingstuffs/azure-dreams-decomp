#include "common.h"

typedef struct S_80017DBC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} S_80017DBC_0;

typedef struct S_80017DBC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80017DBC_1;

typedef struct S_80017DBC_2 {
    u8 pad_00[0xA2];
    s16 unk_A2;
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80017DBC_2;


extern s32 func_800198D0();
extern s32 D_80016470;
extern s32 D_80016608;
extern s32 scene_update_state;
extern s32 scene_choice_index;

/* Marks qualifying entries and their associated state with 0x400 in mode 2. */
s32 mark_qualifying_entries_in_mode_two(void)
{
    s32 entry_index;
    void *source_entry;
    void *dest_entry;
    void *dest_state;

    if (scene_update_state == 2) {
        dest_state = &D_80016608;
        for (entry_index = 1; entry_index < 8; entry_index++) {
            source_entry = (u8 *)&D_80016470 + entry_index * 0xC;
            dest_entry = (u8 *)dest_state + entry_index * 0x14;
            if (func_800198D0(((S_80017DBC_0 *)source_entry)->unk_04) != 0) {
                if (((S_80017DBC_0 *)source_entry)->unk_08 != 0) {
                    ((S_80017DBC_1 *)dest_entry)->unk_02 = 0x400;
                    if (entry_index == 1) {
                        ((S_80017DBC_2 *)dest_state)->unk_A2 = 0x400;
                    } else {
                        ((S_80017DBC_2 *)dest_state)->unk_B6 = 0x400;
                    }
                } else if (scene_choice_index == entry_index) {
                    ((S_80017DBC_1 *)dest_entry)->unk_02 = 0x400;
                }
            }
        }
        return 0;
    }
    return 1;
}
