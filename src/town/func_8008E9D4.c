/* cfail-repair: unary-star-typing; preserve the warm source shape */
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_8008C134_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
} S_8008C134_0;   /* temp_a2 in func_8008C134 */

/* Read the low 14 bits of the map entry at masked tile coordinates. */
s32 func_8008C134(s32 tile_x, s32 tile_y) {
    GameWork *map_state;
    u8 *map_layout;

    map_state = &gameWork;
    map_layout = (u8 *)map_state + 0x1DC;
    return *(u16 *)(((s32) (((((S_8008C134_0 *)map_layout)->unk_18 & tile_x) + ((s16) (((S_8008C134_0 *)map_layout)->unk_1A & tile_y) << ((S_8008C134_0 *)map_layout)->unk_14)) << 0x10) >> 0xF) + ((s32)map_state->map.cells)) & 0x3FFF;
}
