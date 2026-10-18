/* Relink of matched dungeon/func_8125414C; every changed retail word is a paired relocation. */
#define D_80174710 D_80162710
#include "common.h"
#include "shared/tile_object.h"

typedef struct S_8125414C_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8125414C_0;   /* entity in func_8016194C */

typedef struct S_8125414C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8125414C_1;   /* state in func_8016194C */


extern u8 *D_80162710;

extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Repositions the current entity relative to the origin and updates its motion. */
void func_8016194C(s32 offset_index)
{
    s16 offsets[2] = { 1, -1 };
    u8 *object;
    u8 *state;
    u8 *entity;
    void *motion;
    u8 *offset_bytes;
    TileObject *origin;

    object = D_80162710;
    state = object + 0x20;
    entity = *(u8 **)(object + 0xC);
    motion = *(void **)(object + 8);

    ((S_8125414C_0 *)entity)->unk_14 &= 0xFF7F;

    update_map_cell_flags_with_item_limit(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    origin = &D_80082E80;
    offset_bytes = (u8 *)&offsets[offset_index * 2];
    entity[0x24] = origin->tileX + offset_bytes[0];
    entity[0x25] = origin->tileY + offset_bytes[2];

    func_800A2B04(motion, entity[0x24], entity[0x25]);

    cycle_map_cell_flags(entity[0x24], entity[0x25],
                  (((S_8125414C_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);
}
