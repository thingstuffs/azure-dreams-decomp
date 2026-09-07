#include "common.h"

typedef struct DungeonSlot {
    s8 pad_00[0x13];
    u8 field_13;
    u8 pad_14[0x54 - 0x14];
} DungeonSlot;

extern DungeonSlot *D_800E3DF0[];
extern void func_800422DC(DungeonSlot *slot, DungeonSlot *other);

void func_800948BC(void)
{
    DungeonSlot *slot;
    register u8 *record ASM_REG("$17");
    register DungeonSlot **table;
    register s32 expected ASM_REG("$19");
    DungeonSlot *other;
    s32 i;
    u32 index;

    slot = (DungeonSlot *)0x800102F0;
    i = 0x13;
    do {
        slot->field_13 = 0;
        i--;
        slot++;
    } while (i >= 0);

    i = 0;
    expected = 0x13;
    table = D_800E3DF0;
    record = (u8 *)0x8001024B;
    do {
        if (record[-2] == expected) {
            index = record[0] & 0x1F;
            other = table[index];
            if (other != 0) {
                register u32 base ASM_REG("$2");
                base = 0x800102F0;
                func_800422DC((DungeonSlot *)(base + index * 0x54), other);
            }
        }
        i++;
        record += 4;
    } while (i < 0x14);
}
