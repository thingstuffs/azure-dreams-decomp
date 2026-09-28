#include "common.h"
#include "shared/game_work.h"

typedef struct S_80043A68_entry {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u16 flags;
} S_80043A68_entry;


/* Clears flag 0x8000 in four sub-tables at scaled indices 10 and 11. */
void func_80043A68(void)
{
    MapGrid *table = &gameWork.map;
    u8 *base = ((u8 *)table->cells);
    s32 index;

    for (index = 10; index < 12; index++) {
        ((S_80043A68_entry *)(base + (index << table->shiftX) * 6 + 0x78))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->shiftX) * 6 + 0x7E))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->shiftX) * 6 + 0xFC))->flags &= 0x7FFF;
        ((S_80043A68_entry *)(base + (index << table->shiftX) * 6 + 0x102))->flags &= 0x7FFF;
    }
}
