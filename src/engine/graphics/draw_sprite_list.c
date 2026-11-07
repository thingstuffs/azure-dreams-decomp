#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "slus/data.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))


/* Draw the sprite list as textured quads with optional horizontal and vertical flips. */
void draw_sprite_list(void)
{
    SpriteQuadScratch *scratch;
    u8 *packet;
    u8 *sprite_data;
    u8 *prim;
    u8 *sprite;
    u8 *transform_flag;
    u8 **contexts;
    u8 *context;
    s32 tex_start;
    s32 tex_size;
    s16 x_end;
    s16 y_end;
    s32 width;
    s32 height;

    transform_flag = (u8 *)0x1F800094;
    context = g_game_work.draw_buffer;
    scratch = (SpriteQuadScratch *)0x1F800000;
    prim = *(u8 **)(context + 0x8D0);
    contexts = (u8 **)((void * *)(&g_game_work));
    scratch->translation_z = 0;
    scratch->vertices[3].z = 0;
    scratch->vertices[2].z = 0;
    scratch->vertices[1].z = 0;
    scratch->vertices[0].z = 0;
    PushMatrix();

    sprite = scene_sprite_draw_list;
    scratch->translation_x = 0x100;
    scratch->translation_y = 0xB0;
    scratch->rotation_x = 0;
    scratch->rotation_y = 0;
    scratch->rotation_z = 0;
    TransMatrix((void *)0x1F800050, (void *)0x1F800040);
    RotMatrix((void *)0x1F800028, (void *)0x1F800050);
    SetRotMatrix((void *)0x1F800050);
    SetTransMatrix((void *)0x1F800050);

    do {
        tex_start = U8_AT((sprite + 4), 4);
        scratch->uv_u_start = tex_start;
        tex_size = U8_AT((sprite + 4), 6);
        scratch->uv_u_extent = tex_size;
        if (tex_start + tex_size >= 0x100) {
            scratch->uv_u_extent = tex_size - 1;
        }

        tex_start = U8_AT((sprite + 4), 5);
        scratch->uv_v_start = tex_start;
        tex_size = U8_AT((sprite + 4), 7);
        scratch->uv_v_extent = tex_size;
        if (tex_start + tex_size >= 0x100) {
            scratch->uv_v_extent = tex_size - 1;
        }

        if (sprite[0] & 1) {
            s16 x_start;
            x_start = -S8_AT((sprite + 4), -2);
            width = (u16)scratch->uv_u_extent;
            scratch->vertices[2].x = x_start;
            scratch->vertices[0].x = x_start;
            x_end = x_start - width;
            scratch->vertices[3].x = x_end;
            scratch->vertices[1].x = x_end;
        } else {
            s16 x_start;
            x_start = S8_AT((sprite + 4), -2);
            width = (u16)scratch->uv_u_extent;
            scratch->vertices[2].x = x_start;
            scratch->vertices[0].x = x_start;
            x_end = x_start + width;
            scratch->vertices[3].x = x_end;
            scratch->vertices[1].x = x_end;
        }

        if (sprite[0] & 2) {
            s16 y_start;
            y_start = -S8_AT((sprite + 4), -1);
            height = (u16)scratch->uv_v_extent;
            scratch->vertices[1].y = y_start;
            scratch->vertices[0].y = y_start;
            y_end = y_start - height;
            scratch->vertices[3].y = y_end;
            scratch->vertices[2].y = y_end;
        } else {
            s16 y_start;
            y_start = S8_AT((sprite + 4), -1);
            height = (u16)scratch->uv_v_extent;
            scratch->vertices[1].y = y_start;
            scratch->vertices[0].y = y_start;
            y_end = y_start + height;
            scratch->vertices[3].y = y_end;
            scratch->vertices[2].y = y_end;
        }

        RotTransSV(&scratch->vertices[0], prim + 0x08, transform_flag);
        RotTransSV(&scratch->vertices[1], prim + 0x10, transform_flag);
        RotTransSV(&scratch->vertices[2], prim + 0x18, transform_flag);
        RotTransSV(&scratch->vertices[3], prim + 0x20, transform_flag);

        scratch->uv_u_extent += scratch->uv_u_start;
        scratch->uv_v_extent =
            (scratch->uv_v_extent + scratch->uv_v_start) << 8;
        scratch->uv_v_start <<= 8;

        U16_AT((prim + 4), 0x0A) = U16_AT((sprite + 4), 2);
        S16_AT((prim + 4), 0x08) = (u16)scratch->uv_v_start + (u16)scratch->uv_u_start;
        S16_AT((prim + 4), 0x10) = (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;
        U16_AT((prim + 4), 0x12) = U16_AT((sprite + 4), 0);
        S16_AT((prim + 4), 0x18) = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
        S16_AT((prim + 4), 0x20) = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_extent;

        if (S16_AT((prim + 4), 0x04) > S16_AT((prim + 4), 0x1C)) {
            u8 u_end = U8_AT((prim + 4), 0x20);
            U8_AT((prim + 4), 0x20) = u_end + 0xFF;
            U8_AT((prim + 4), 0x10) = u_end;
        }
        if (S16_AT((prim + 4), 0x06) > S16_AT((prim + 4), 0x1E)) {
            u8 v_end = U8_AT((prim + 4), 0x21);
            U8_AT((prim + 4), 0x21) = v_end + 0xFF;
            U8_AT((prim + 4), 0x19) = v_end;
        }

        U8_AT((prim + 4), -1) = 9;
        U8_AT((prim + 4), 3) = 0x2C;
        U8_AT((prim + 4), 2) = 0x80;
        U8_AT((prim + 4), 1) = 0x80;
        U8_AT((prim + 4), 0) = 0x80;
        DrawPrim(prim);
        packet = (prim + 4) + 0x28;
        prim += 0x28;
        if ((s8)sprite[0] < 0) {
            break;
        }
        sprite_data = (sprite + 4) + 0xC;
        sprite += 0xC;
    } while (1);

    PopMatrix();
    *(u8 **)(contexts[0] + 0x8D0) = prim;
}
