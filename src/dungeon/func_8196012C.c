#include "modules/dungeon_ovl_197e800.h"
#include "modules/dungeon_draw_chain.h"

#ifndef NULL
#define NULL 0
#endif

   /* object in func_8002592C */

   /* position in func_8002592C */

   /* render in func_8002592C */

   /* primitive in func_8002592C */


struct RegistrationNode;
extern s32 rand();

/* Spawn a textured particle with randomized motion at the given position. */
void func_8002592C(s16 x, s16 y, s16 z, s16 tile_col, s16 tile_row) {
    s32 random_angle;
    s32 primitive_word;
    s16 tile_row_copy;
    S_8196012C_1 *position;
    S_8196012C_3 *primitive;
    S_8196012C_2 *render;
    void *object;

    tile_row_copy = tile_row;
    object = func_8003FC64(0x202);
    if (object != NULL) {
        ((S_8196012C_0 *)object)->unk_10 = func_80025460;
        func_8004491C(object, (s32)func_800258D8);
        position = ((S_8196012C_0 *)object)->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = z;
        position->unk_0E = (rand() & 0xF) - 8;
        position->unk_12 = (rand() & 0xF) - 8;
        position->unk_16 = -0x10 - (rand() & 0xF);
        render = ((S_8196012C_0 *)object)->unk_0C;
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;
        random_angle = rand();
        render->unk_20 = func_80064584(random_angle);
        render->unk_22 = func_800644B8(random_angle);
        render->unk_10 = 0x20;
        primitive = (s8 *)object + 0x20;
        render->unk_14 = 0xC;
        render->unk_0C = 0x808080;
        primitive_word = 0xF8F82CC0;
        ((S_8196012C_0 *)object)->unk_20 = primitive_word;
        primitive->unk_04 = 0x13D;
        primitive->unk_08 = (s8)(tile_col * 0x10);
        primitive->unk_09 = (s8)(((s32)(tile_row << 0x10) >> 0xC) - 0x80);
        primitive->unk_0A = tile_col == 7 ? 0xF : 0x10;
        primitive->unk_0B = tile_row_copy == 7 ? 0xF : 0x10;
        primitive->unk_4C = (rand(primitive_word) & 0x1F) + 0x20;
        render->unk_08 = primitive;
    }
}
