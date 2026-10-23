#include "dungeon/effect/sprite/offset_parent.h"


/* Projects two vertical points per linked node and queues a textured quad using the node's tile index. */
s32 handle_spawn_initialize_randomized_offset_parent(void *sprite_data, void *position)
{
    u16 world_pos[4];
    s16 screen_points[4];
    Row_818E6F98_WorkOutput scratch;
    u8 *uv_source;
    Row_818E6F98_DungeonState **state_address;
    s16 *screen_base;
    Row_818E6F98_WorkOutput *scratch_base;
    s16 *screen_cursor;
    s32 point_index;
    u32 ordering_index;
    s32 width;
    Row_818E6F98_Primitive *primitive;
    Row_818E6F98_DungeonState *state;
    Row_818E6F98_DungeonState *table_state;
    s32 uv;
    s32 uv_low;
    s32 uv_high;
    s32 node;
    u16 half_width;
    u16 center_x;
    u32 table_offset;

    state_address = (Row_818E6F98_DungeonState **)((u8 *)(&g_game_work));
    screen_base = screen_points;
    scratch_base = &scratch;
loop:
    uv_source = sprite_data;
    world_pos[0] = *(u16 *)((u8 *)position + 2);
    world_pos[1] = *(u16 *)((u8 *)position + 6);
    world_pos[2] = *(u16 *)((u8 *)position + 0xA) - 0x20;
    point_index = 0;
    screen_cursor = screen_base;
    do {
        ordering_index =
            RotTransPers(world_pos, screen_cursor, scratch_base, scratch_base);
        ordering_index -= 8;
        screen_cursor += 2;
        point_index++;
        world_pos[2] += 0x40;
    } while (point_index < 2);

    width = screen_points[1] - screen_points[3];
    if (ordering_index < 0x1E0U) {
        state = *state_address;
        primitive = state->next_primitive;
        state->next_primitive = primitive + 1;
        primitive->color = 0x00C0C0C0;
        SetPolyFT4(primitive);
        SetSemiTrans(primitive, 1);
        primitive->tpage = GetTPage(0, 1, 0x2C0, 0x100);
        primitive->clut = GetClut(0x20, 0x1F8);

        scratch.w[0] = width >> 1;
        center_x = screen_points[0];
        half_width = scratch.h[0];
        primitive->x0 = primitive->x1 = center_x + half_width;
        primitive->x2 = primitive->x3 = screen_points[0] - half_width;
        primitive->y0 = primitive->y2 = screen_points[1];
        primitive->y1 = primitive->y3 = screen_points[3];

        uv = *(u8 *)(uv_source + 0x52);
        table_offset = ordering_index << 2;
        uv = (uv & 3) << 5;
        uv_low = uv - 0x80;
        uv_high = uv - 0x61;
        primitive->u0 = primitive->u1 = uv_low;
        primitive->u2 = primitive->u3 = uv_high;

        uv = ((s16)*(u16 *)(uv_source + 0x52) >> 2) << 5;
        uv_low = uv - 0x80;
        uv_high = uv - 0x61;
        primitive->v0 = primitive->v2 = uv_low;
        primitive->v1 = primitive->v3 = uv_high;

        table_state = *state_address;
        (*(u32 *)((u8 *)primitive + 0)) = (primitive->tag & 0xFF000000) |
                         (*(u32 *)((u8 *)table_state + 0xB0 + table_offset) &
                          0x00FFFFFF);
        table_state = *state_address;
        *(u32 *)((u8 *)table_state + 0xB0 + table_offset) =
            (*(u32 *)((u8 *)table_state + 0xB0 + table_offset) & 0xFF000000) |
            ((u32)primitive & 0x00FFFFFF);
    }

    node = *(s32 *)((u8 *)sprite_data - 8);
    uv_source = (u8 *)node + 0x20;
    sprite_data = uv_source;
    if (node != 0) {
        position = *(void **)(node + 8);
        goto loop;
    }
    {
        s32 zero = 0;

        return zero;
    }
}
