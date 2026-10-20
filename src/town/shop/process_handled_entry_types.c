#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B6B10_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_2;

typedef struct S_800B6B10_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B6B10_3;

typedef struct S_800B6B10_4 {
    u8 pad_00[0xE];
    u8 unk_0E;
} S_800B6B10_4;

typedef struct S_800B6B10_5 {
    u8 pad_00[0xE];
    s8 unk_0E;
} S_800B6B10_5;

M2C_UNK func_8004B1A4();
M2C_UNK func_8004E99C();

typedef struct S_800B6B10_0 {
    s32 unk_00;
} S_800B6B10_0;

typedef struct S_800B6B10_1 {
    s32 unk_00;
} S_800B6B10_1;

/* Processes 24 entries by type and clears the handle and type of handled entries. */
void process_handled_entry_types(void **entries) {
    s32 entry_index;
    u8 entry_type;
    S_800B6B10_0 *entry;

    for (entry_index = 0; entry_index < 0x18; entry_index++) {
        entry = entries[entry_index];
        entry_type = ((S_800B6B10_4 *)(((S_800B6B10_2 *)entry)->unk_04))->unk_0E;
        if (entry_type == 2) {
            func_8004E99C(entry->unk_00);
            ((S_800B6B10_1 *)entries[entry_index])->unk_00 = 0;
            ((S_800B6B10_5 *)(((S_800B6B10_3 *)entries[entry_index])->unk_04))->unk_0E = 0;
        } else if (entry_type == 1) {
            func_8004B1A4(entry->unk_00);
            ((S_800B6B10_1 *)entries[entry_index])->unk_00 = 0;
            ((S_800B6B10_5 *)(((S_800B6B10_3 *)entries[entry_index])->unk_04))->unk_0E = 0;
        }
    }

}
