#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"

typedef struct S_8016EC04_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8016EC04_1;   /* state in relocate_multi_form_actor */

extern u8 *D_80175D50;

extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Reposition the current entity relative to the origin using the selected offset. */
void relocate_multi_form_actor(s32 offset_index)
{
    s16 delta[2] = { 0, -12 };
    u8 *object;
    u8 *state;
    u8 *entity;
    void *motion;
    u8 *step;
    TileObject *origin;

    object = D_80175D50;
    state = object + 0x20;
    entity = *(u8 **)(object + 0xC);
    motion = *(void **)(object + 8);

    ((SpriteFrameState *)entity)->flags &= 0xFF7F;

    update_map_cell_flags_with_item_limit(entity[0x24], entity[0x25],
                  (((S_8016EC04_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);

    origin = &D_80082E80;
    step = (u8 *)&delta[offset_index * 2];
    entity[0x24] = origin->tileX + step[0];
    entity[0x25] = origin->tileY + step[2];

    set_record_integer_tile_center(motion, entity[0x24], entity[0x25]);

    cycle_map_cell_flags(entity[0x24], entity[0x25],
                  (((S_8016EC04_1 *)state)->unk_1C & 0x2000) ? 0x300 : 0x3000);
}
