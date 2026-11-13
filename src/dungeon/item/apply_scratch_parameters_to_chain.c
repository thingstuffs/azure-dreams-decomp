#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/screen.h"
#include "sdk/libgte.h"
#include "dungeon/item.h"
#include "engine/graphics/sprite_scratch.h"

   /* arg1 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_2 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_80099A1C_2;   /* arg2 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_3_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80099A1C_3_pre;   /* the 0x8 bytes before arg0 in apply_scratch_parameters_to_chain, addressed as arg0[-1] */

typedef struct S_80099A1C_3 {
    u16 unk_00;
    u8 pad_02[0x6];
    s32 unk_08;
    s16 unk_0C;
} S_80099A1C_3;   /* arg0 in apply_scratch_parameters_to_chain */

typedef struct S_80099A1C_4 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_80099A1C_4;   /* next in apply_scratch_parameters_to_chain */

/* Build scratch parameters and apply them to each object in a linked chain. */
s32 apply_scratch_parameters_to_chain(void *object, MovingPosition *position, S_80099A1C_2 *offset_data)
{
    SpriteQuadScratch *scratch;
    S_80099A1C_4 *next_node;
    s32 transform_result;

    scratch = (SpriteQuadScratch *)0x1F800000;

    do {
        scratch->position.vx = position->x;
        scratch->position.vy = position->y;
        scratch->position.vz = position->z;

        transform_result = RotTransPers(
            &scratch->position,
            (s32 *)&scratch->screen_origin,
            &scratch->depth_cue,
            &scratch->gte_flag);
        scratch->sort_depth = transform_result - offset_data->unk_06;

        {
            s32 half_offset;
            u32 adjusted_coord;

            half_offset = ((S_80099A1C_3 *)object)->unk_00;
            adjusted_coord = scratch->screen_origin.x;
            half_offset = (half_offset << 16) >> 17;
            adjusted_coord -= half_offset;
            scratch->screen_origin.x = adjusted_coord;
        }
        scratch->screen_origin.x +=
            (rsin(
                (((S_80099A1C_3 *)object)->unk_0C << 8) +
                (((S_80099A1C_3 *)object)->unk_08 << 7)) *
             (((S_80099A1C_3 *)object)->unk_08 >> 2)) >> 9;

        queue_visible_rectangle_copy(object, scratch);

        next_node = ((S_80099A1C_3_pre *)object)[-1].unk_00;
        object = NODE_BODY(next_node);
        if (next_node == 0) {
            break;
        }
        position = next_node->unk_08;
        offset_data = next_node->unk_0C;
    } while (1);
    return 0;
}
