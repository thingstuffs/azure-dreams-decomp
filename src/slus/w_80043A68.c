#include "common.h"

typedef struct S_80043A68_entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 flags;
} S_80043A68_entry;

typedef struct S_8008333C {
    /* 0x00 */ u8 *field0;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ s16 field14;
} S_8008333C;

extern S_8008333C D_8008333C;

/* Clears flag 0x8000 in four sub-table entries for each scaled index 10 and 11. */
void func_80043A68(void)
{
    S_8008333C *table = &D_8008333C;
    u8 *base = table->field0;
    s32 index;

    for (index = 10; index < 12; index++) {
        ((S_80043A68_entry *)(base + (index << table->field14) * 6 + 0x78))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->field14) * 6 + 0x7E))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->field14) * 6 + 0xFC))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->field14) * 6 + 0x102))->flags &= 0x7FFF;
    }
}
