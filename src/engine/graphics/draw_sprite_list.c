#include "common.h"
#include "shared/game_work.h"
#include "engine/graphics/sprite_scratch.h"
#include "engine/graphics.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "slus/data.h"
#include "shared/gpu_packets.h"
#include "sdk/libgpu_packets.h"

#define U8_AT(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S8_AT(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))


/* Draw the sprite list as textured quads with optional horizontal and vertical flips. */
void draw_sprite_list(void)
{
    SpriteQuadScratch *scratch;
    u8 *sprite_data;
    POLY_FT4 *prim;
    u8 *sprite;
    s32 *transform_flag;
    GpuContext **contexts;
    GpuContext *context;
    s32 tex_start;
    s32 tex_size;
    s16 x_end;
    s16 y_end;
    s32 width;
    s32 height;

    context = g_game_work.draw_buffer;
    scratch = (SpriteQuadScratch *)0x1F800000;
    transform_flag = &scratch->gte_flag;
    prim = context->packetCursor;
    contexts = (GpuContext **)&g_game_work;
    scratch->translation.vz = 0;
    scratch->vertices[3].vz = 0;
    scratch->vertices[2].vz = 0;
    scratch->vertices[1].vz = 0;
    scratch->vertices[0].vz = 0;
    PushMatrix();

    sprite = scene_sprite_draw_list;
    scratch->translation.vx = 0x100;
    scratch->translation.vy = 0xB0;
    scratch->rotation.vx = 0;
    scratch->rotation.vy = 0;
    scratch->rotation.vz = 0;
    TransMatrix(&scratch->matrix, &scratch->translation);
    RotMatrix(&scratch->rotation, &scratch->matrix);
    SetRotMatrix(&scratch->matrix);
    SetTransMatrix(&scratch->matrix);

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
            scratch->vertices[2].vx = x_start;
            scratch->vertices[0].vx = x_start;
            x_end = x_start - width;
            scratch->vertices[3].vx = x_end;
            scratch->vertices[1].vx = x_end;
        } else {
            s16 x_start;
            x_start = S8_AT((sprite + 4), -2);
            width = (u16)scratch->uv_u_extent;
            scratch->vertices[2].vx = x_start;
            scratch->vertices[0].vx = x_start;
            x_end = x_start + width;
            scratch->vertices[3].vx = x_end;
            scratch->vertices[1].vx = x_end;
        }

        if (sprite[0] & 2) {
            s16 y_start;
            y_start = -S8_AT((sprite + 4), -1);
            height = (u16)scratch->uv_v_extent;
            scratch->vertices[1].vy = y_start;
            scratch->vertices[0].vy = y_start;
            y_end = y_start - height;
            scratch->vertices[3].vy = y_end;
            scratch->vertices[2].vy = y_end;
        } else {
            s16 y_start;
            y_start = S8_AT((sprite + 4), -1);
            height = (u16)scratch->uv_v_extent;
            scratch->vertices[1].vy = y_start;
            scratch->vertices[0].vy = y_start;
            y_end = y_start + height;
            scratch->vertices[3].vy = y_end;
            scratch->vertices[2].vy = y_end;
        }

        RotTransSV(&scratch->vertices[0], &prim->x0, transform_flag);
        RotTransSV(&scratch->vertices[1], &prim->x1, transform_flag);
        RotTransSV(&scratch->vertices[2], &prim->x2, transform_flag);
        RotTransSV(&scratch->vertices[3], &prim->x3, transform_flag);

        scratch->uv_u_extent += scratch->uv_u_start;
        scratch->uv_v_extent =
            (scratch->uv_v_extent + scratch->uv_v_start) << 8;
        scratch->uv_v_start <<= 8;

        prim->clut = U16_AT((sprite + 4), 2);
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&prim->u0 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&prim->u1 = (u16)scratch->uv_v_start + (u16)scratch->uv_u_extent;
        prim->tpage = U16_AT((sprite + 4), 0);
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&prim->u2 = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_start;
        /* BYTES: retail writes the packet u/v byte pair with one sh of the combined value; storing u and v separately compiles to two sb */
        *(u16 *)&prim->u3 = (u16)scratch->uv_v_extent + (u16)scratch->uv_u_extent;

        if (prim->x0 > prim->x3) {
            u8 u_end = prim->u3;
            prim->u3 = u_end + 0xFF;
            prim->u1 = u_end;
        }
        if (prim->y0 > prim->y3) {
            u8 v_end = prim->v3;
            prim->v3 = v_end + 0xFF;
            prim->v2 = v_end;
        }

        ((GpuLinkTag *)&prim->tag)->len = 9;
        prim->code = 0x2C;
        prim->b0 = 0x80;
        prim->g0 = 0x80;
        prim->r0 = 0x80;
        DrawPrim(prim);
        prim++;
        if ((s8)sprite[0] < 0) {
            break;
        }
        sprite_data = (sprite + 4) + 0xC;
        sprite += 0xC;
    } while (1);

    PopMatrix();
    contexts[0]->packetCursor = prim;
}
