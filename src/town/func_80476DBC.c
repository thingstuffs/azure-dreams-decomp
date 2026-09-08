#include "common.h"

typedef struct S_80017DBC_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x2];
    s32 unk_08;
} S_80017DBC_0;   /* var_s0 in func_80017DBC */

typedef struct S_80017DBC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
} S_80017DBC_1;   /* var_s2 in func_80017DBC */

typedef struct S_80017DBC_2 {
    u8 pad_00[0xA2];
    s16 unk_A2;
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80017DBC_2;   /* var_s4 in func_80017DBC */



extern s32 func_800198D0();
extern s32 D_80016470;
extern s32 D_80016608;
extern s32 D_80019BB0;
extern s32 D_80019BB4;

/* Marks qualifying entries and their associated state with 0x400 in mode 2. */
s32 func_80017DBC(void)
{
    s32 entry_index;
    s32 mark_value;
    void *source_entry;
    void *dest_entry;
    void *dest_state;
    s32 entry_offset;

    if (D_80019BB0 == 2) {
        do { entry_index = 1; } while (0);
        mark_value = 0x400;
        dest_state = &D_80016608;
        dest_entry = dest_state + 0x14;
        do {
            entry_offset = 0xC;
            source_entry = (u8 *)&D_80016470 + entry_offset;
        } while (0);
check_entry:
        if (func_800198D0(((S_80017DBC_0 *)source_entry)->unk_04) != 0) {
            if (((S_80017DBC_0 *)source_entry)->unk_08 != 0) {
                ((S_80017DBC_1 *)dest_entry)->unk_02 = mark_value;
                if (entry_index == 1) {
                    ((S_80017DBC_2 *)dest_state)->unk_A2 = mark_value;
                    goto next_entry;
                }
                ((S_80017DBC_2 *)dest_state)->unk_B6 = mark_value;
                goto next_entry;
            }
            if (D_80019BB4 == entry_index) {
                ((S_80017DBC_1 *)dest_entry)->unk_02 = mark_value;
            }
        }
next_entry:
        dest_entry += 0x14;
        entry_index += 1;
        source_entry += 0xC;
        if (entry_index >= 8) {
            return 0;
        }
        goto check_entry;
    }
    return 1;
}
