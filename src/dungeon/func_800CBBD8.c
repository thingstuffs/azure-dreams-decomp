#include "common.h"

extern s16 D_80080B00[8];
extern u8 D_8008333C[32];
extern u8 D_800E6000[16400];
extern u8 *D_80081508;

/* Clear flag 0x80 on the listed tiles and reset the list. */
void func_800D1338(void) {
    u8 *entry;
    u8 *tile;
    u16 tile_flags;
    u8 *map_config;

    map_config = D_8008333C;
    entry = D_80081508;
    if (*entry != 0) {
        do {
            tile = &D_800E6000[0x4000 + (entry[0] + (entry[1] << *(s16 *)(map_config + 0x14))) * 6];
            tile_flags = *(u16 *)(tile + 4);
            entry += 4;
            *(s16 *)(tile + 4) = (s16)(tile_flags & 0xFF7F);
        } while (*entry != 0);
    }
    *(s16 *)((u8 *)D_80080B00 + 4) = 0;
    *D_80081508 = 0;
}
