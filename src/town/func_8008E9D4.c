/* cfail-repair: unary-star-typing; preserve the warm source shape */
#include "common.h"
#include "m2c_compat.h"

struct S_8003E2D8 {
    u8 byte_0;
};
extern struct S_8003E2D8 D_80083160;

typedef struct S_8008C134_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
} S_8008C134_0;   /* temp_a2 in func_8008C134 */

typedef struct S_8008C134_1 {
    u8 pad_00[0x1DC];
    s32 unk_1DC;
} S_8008C134_1;   /* temp_a3 in func_8008C134 */

/* Read the low 14 bits of the map entry at masked tile coordinates. */
s32 func_8008C134(s32 tile_x, s32 tile_y) {
    u8 *map_state;
    u8 *map_layout;

    map_state = (u8 *)&D_80083160;
    ASM_KEEP(map_state);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    map_layout = map_state + 0x1DC;
    ASM_KEEP(map_layout);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    return *(u16 *)(((s32) (((((S_8008C134_0 *)map_layout)->unk_18 & tile_x) + ((s16) (((S_8008C134_0 *)map_layout)->unk_1A & tile_y) << ((S_8008C134_0 *)map_layout)->unk_14)) << 0x10) >> 0xF) + ((S_8008C134_1 *)map_state)->unk_1DC) & 0x3FFF;
}
