#include "common.h"

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

extern DungeonSlot *D_800E3DF0[];

s32 func_800A4298(DungeonSlot *arg0) {
    s32 i;
    s32 magic;
    DungeonSlot **table;
    u8 *record;
    s32 index;

    i = 0;
    magic = 0x13;
    table = D_800E3DF0;
    record = (u8 *) 0x8001024B;
    do {
        if (record[-2] == magic) {
            index = record[0] & 0x1F;
            if (table[index] == arg0) {
                return index;
            }
        }
        i++;
        record += 4;
    } while (i < 0x14);
    return -1;
}
