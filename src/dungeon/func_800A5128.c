#include "common.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_func_800AA258_arg2.h"


typedef s32 M2C_UNK;


typedef struct S_800AA888_4 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_800AA888_4;   /* ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in func_800AA888 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_8009A3D0();


/* Reset action state, update the tile, and refresh entity flags and data. */
void func_800AA888(Rec_func_800A9E70_arg0 *state, void *unused, Rec_func_800AA258_arg2 *position, EntityRec *entity) {
    u8 tile_x;
    u8 tile_y;
    M2C_UNK update_mask;

    state->unk_9A.as_s8 = 0xB;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    tile_x = position->unk_24;
    tile_y = position->unk_25;
    update_mask = 0x3000;
    if (entity->flags1C & 0x2000) {
        update_mask = 0x300;
    }
    func_8009A3D0(tile_x, tile_y, update_mask);
    state->unk_98 = (u16)(state->unk_98 | 8);
    entity->flags1C = (s32)(entity->flags1C & 0xFFFBFFFF);
    state->unk_96.as_s16 = 0;
    entity->unk_6A = (u16)((S_800AA888_4 *)(((EntityRec *)entity)->target))->unk_2A;
}
