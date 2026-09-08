#include "common.h"

typedef struct {
    s32 words[2];
    s16 field_8;
    s16 field_A;
    s16 field_C;
    s16 field_E;
    s32 field_10;
} DungeonEntry;

extern s16 D_8008146E[5];
extern DungeonEntry D_800E2970[];

/* Compact occupied dungeon entries, clear the unused tail, and update the count. */
void func_800176EC(void) {
    s8 *read_entry;
    s8 *write_entry;
    s32 entry_count;
    s32 entry_index;

    do { entry_index = 0; } while (0);
    entry_count = 0;
    read_entry = (s8 *)D_800E2970;
    write_entry = (s8 *)D_800E2970;
    do {
        if (*(s16 *)(read_entry + 0xA) != 0) {
            if (entry_index != entry_count) {
                *(DungeonEntry *)write_entry = *(DungeonEntry *)read_entry;
            }
            write_entry += 0x14;
            entry_count += 1;
        }
        entry_index += 1;
        read_entry += 0x14;
    } while (entry_index < 0x24);

    entry_index = entry_count;
    if (entry_count < 0x24) {
        do {
            D_800E2970[entry_index].field_A = 0;
            D_800E2970[entry_index].field_E = 0;
            D_800E2970[entry_index].field_10 = 0;
        } while (++entry_index < 0x24);
    }
    D_8008146E[0] = entry_count;
}
