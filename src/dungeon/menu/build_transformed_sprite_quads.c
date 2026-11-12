#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/vector.h"
#include "dungeon/menu.h"
#include "shared/game_work.h"
#include "records/Rec_D_80083160.h"
#include "slus.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

/* Scratchpad work area (0x1F800000) used while building the sprite quads: the GTE rotation, scale and
 * transform inputs, the four corner vectors and the texture rectangle of the selected frame. */
typedef struct SpriteQuadScratch {
    /* 0x00 */ u16 origin_x; /* placement X; the transform translates by it and the projected center subtracts it */
    /* 0x02 */ u16 origin_y; /* placement Y */
    u8 pad_04[0x4];
    /* 0x08 */ s32 tex_u; /* frame texture left U; shifted into the packed UV words */
    /* 0x0C */ s32 tex_v; /* frame texture top V */
    /* 0x10 */ s32 tex_width; /* frame texture width, then advanced to the right U */
    /* 0x14 */ s32 tex_height; /* frame texture height, then advanced to the bottom V */
    u8 pad_18[0x8];
    /* 0x20 */ u8 *order_table; /* ordering table of the current draw context */
    /* 0x24 */ u16 sprite_flags; /* copy of the sprite's flags */
    u8 pad_26[0x2];
    /* 0x28 */ SVECTOR center_offset; /* offset of the sprite center from its extent, rotated to find the screen center */
    /* 0x30 */ IntVector3 scale; /* ScaleMatrix scale vector */
    u8 pad_3C[0xC];
    /* 0x48 */ s32 unk_48;
    u8 pad_4C[0x24];
    /* 0x70 */ SVECTOR corners[4]; /* the four frame corners passed to RotTransSV */
    u8 pad_90[0x4];
    /* 0x94 */ s32 gte_flags; /* RotTransSV flag output */
    /* 0x98 */ SVECTOR rotation; /* RotMatrix angles; only the view angle is nonzero */
    u8 pad_A0[0x30];
    /* 0xD0 */ MATRIX transform; /* rotation, scale and placement translation */
    u8 pad_F0[0x10];
    /* 0x100 */ u16 center_x; /* projected sprite center X, made relative to the placement */
    /* 0x102 */ u16 center_y; /* projected sprite center Y, made relative to the placement */
} SpriteQuadScratch;


typedef struct S_8009E798_5_pre {
    u32 unk_00;
    u8 pad_04[0x4];
    u32 unk_08;
    u8 pad_0C[0x4];
    u32 unk_10;
    u8 pad_14[0x4];
    u32 unk_18;
    u8 pad_1C[0x4];
} S_8009E798_5_pre;   /* 0x20-byte header immediately before the payload. */

typedef struct S_8009E798_5 {
    u8 pad_00[0x2];
    u8 unk_02;
    u8 unk_03;
    union {
        struct { s16 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 v; } at00p;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u16 v; } at02;
        struct { u8 pad[0x2]; u8 v; } at02u;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_04;   /* overlapping accesses */
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_08;   /* overlapping accesses */
    u32 unk_0C;
    u32 unk_10;
    u32 unk_14;
} S_8009E798_5;

typedef struct S_8009E798_6 {
    u8 pad_00[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x4];
    u16 unk_0C;
    u16 unk_0E;
    u8 pad_10[0x12];
    u16 unk_22;
    u16 unk_24;
} S_8009E798_6;   /* packet in build_transformed_sprite_quads */

   /* ret_state in build_transformed_sprite_quads */


extern u8 upper_draw_context[16];

/* Build and enqueue transformed sprite quads and restore the drawing area. */
s32 build_transformed_sprite_quads(InactiveTypeTwelveObjectBody *draw_area, ObjectPosition *placement, SpriteFrameState *sprite)
{
    u8 **state_ptr = (u8 **)((u8 *)(&g_game_work));
    u8 *state = *state_ptr;
    SpriteQuadScratch *scratch = (SpriteQuadScratch *)0x1F800000;
    u8 *packet = ((GpuContext *)state)->packetCursor;
    S_8009E798_5 *frame;
    u8 *copy;
    u8 *prim;
    PolyFT4 *copied_quad;
    s16 lower_buffer = state != upper_draw_context;
    s16 vertex_y;
    s16 vertex_x;
    u16 rect[4];

    scratch->order_table = state + 0xB0;
    scratch->scale.z = 0x1000;
    scratch->unk_48 = 0;

    SetDrawArea(packet, state);
    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  packet);

    scratch->scale.x = sprite->scale_x;
    scratch->scale.y = sprite->scale_y;
    scratch->origin_x = placement->x.unsigned_parts.integer;
    scratch->origin_y = placement->y.unsigned_parts.integer;
    frame = (S_8009E798_5 *)sprite->source;
    scratch->sprite_flags = sprite->flags;
    PushMatrix();

    scratch->rotation.vx = 0;
    scratch->rotation.vy = 0;
    scratch->rotation.vz = ((u16)(g_game_work.view.camera_rotation.parts.viewAngle));
    RotMatrix(&scratch->rotation, &scratch->transform);
    ScaleMatrix(&scratch->transform, &scratch->scale);

    scratch->transform.t[2] = 0;
    scratch->transform.t[0] = ((s16)scratch->origin_x);
    scratch->transform.t[1] = (s16)scratch->origin_y;
    SetRotMatrix(&scratch->transform);
    SetTransMatrix(&scratch->transform);

    scratch->center_offset.vx = 0x20 - sprite->offset_x;
    scratch->center_offset.vy = 0x20 - sprite->offset_y;
    scratch->center_offset.vz = 0;
    RotTransSV(&scratch->center_offset, &scratch->center_x, &scratch->gte_flags);

    packet += 0xC;
    scratch->center_x -= scratch->origin_x;
    scratch->center_y -= scratch->origin_y;

    scratch->tex_u = frame->unk_08.at00.v;
    scratch->tex_v = frame->unk_08.at01.v;
    scratch->tex_width = frame->unk_08.at02.v;
    scratch->tex_height = frame->unk_08.at03.v;

    vertex_x = (s8)frame->unk_02;
    scratch->corners[2].vx = vertex_x;
    scratch->corners[0].vx = vertex_x;
    vertex_x += scratch->tex_width;
    scratch->corners[3].vx = vertex_x;
    scratch->corners[1].vx = vertex_x;

    vertex_y = (s8)frame->unk_03;
    scratch->corners[3].vz = 0;
    scratch->corners[2].vz = 0;
    scratch->corners[1].vz = 0;
    scratch->corners[0].vz = 0;
    scratch->corners[1].vy = vertex_y;
    scratch->corners[0].vy = vertex_y;
    vertex_y += scratch->tex_height;
    scratch->corners[3].vy = vertex_y;
    scratch->corners[2].vy = vertex_y;

    RotTransSV(&scratch->corners[0], packet + 8, &scratch->gte_flags);
    RotTransSV(&scratch->corners[1], packet + 0x10, &scratch->gte_flags);
    RotTransSV(&scratch->corners[2], packet + 0x18, &scratch->gte_flags);
    RotTransSV(&scratch->corners[3], packet + 0x20, &scratch->gte_flags);

    (*(u16 *)(packet + 8)) += scratch->center_x;
    (*(u16 *)(packet + 0x10)) += scratch->center_x;
    (*(u16 *)(packet + 0x18)) += scratch->center_x;
    (*(u16 *)(packet + 0x20)) += scratch->center_x;
    (*(u16 *)(packet + 0xA)) += scratch->center_y;
    (*(u16 *)(packet + 0x12)) += scratch->center_y;
    (*(u16 *)(packet + 0x1A)) += scratch->center_y;
    ((S_8009E798_6 *)packet)->unk_22 += scratch->center_y;

    scratch->tex_width += scratch->tex_u;
    scratch->tex_height =
        (scratch->tex_height + scratch->tex_v) << 8;
    scratch->tex_v <<= 8;

    ((S_8009E798_6 *)packet)->unk_0E = sprite->clut
        + frame->unk_04.at02.v;
    ((S_8009E798_6 *)packet)->unk_0C = scratch->tex_v + scratch->tex_u;
    (*(s32 *)(packet + 0x14)) = scratch->tex_v +
        scratch->tex_width +
        ((sprite->tpage_abr | frame->unk_04.at00.v) << 16);
    (*(u16 *)(packet + 0x1C)) = scratch->tex_height + scratch->tex_u;
    ((S_8009E798_6 *)packet)->unk_24 = scratch->tex_height + scratch->tex_width;
    ((S_8009E798_6 *)packet)->unk_04.at00.v = sprite->color.word;
    SetPolyFT4(packet);

    copy = packet + 0x28;
    copy_words_forward(copy, packet, 0xA);
    ((S_8009E798_6 *)packet)->unk_04.at03.v |= 2;
    packet = copy;
    prim = packet + 0x28;
    copied_quad = (PolyFT4 *)packet;
    copied_quad->v0 = (copied_quad->v1 += 0x40);
    copied_quad->v2 = (copied_quad->v3 += 0x40);
    copied_quad->tpage |= 0x100;

    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  packet);
    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  packet - 0x28);

    ((S_8009E798_5 *)prim)->unk_04.at00u.v = 0x00606060;
    ((S_8009E798_5 *)prim)->unk_08.at00u.v = ((S_8009E798_5_pre *)prim)[-1].unk_00;
    ((S_8009E798_5 *)prim)->unk_0C = ((S_8009E798_5_pre *)prim)[-1].unk_08;
    ((S_8009E798_5 *)prim)->unk_10 = ((S_8009E798_5_pre *)prim)[-1].unk_10;
    ((S_8009E798_5 *)prim)->unk_14 = ((S_8009E798_5_pre *)prim)[-1].unk_18;
    ((S_8009E798_5 *)prim)->unk_04.at00p.v >>= 1;
    ((S_8009E798_5 *)prim)->unk_04.at01.v >>= 1;
    ((S_8009E798_5 *)prim)->unk_04.at02u.v >>= 1;
    SetPolyF4(prim);
    ((S_8009E798_5 *)prim)->unk_04.at03.v |= 2;

    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  prim);
    prim = packet + 0x40;
    SetDrawMode(prim, 0, 0, 0x40, 0);
    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  prim);

    rect[0] = draw_area->view_x;
    rect[1] = draw_area->view_y;
    rect[2] = draw_area->view_width;
    rect[3] = draw_area->view_height;
    prim = packet + 0x4C;
    if (lower_buffer) {
        rect[1] += 0xE0;
    }

    SetDrawArea(prim, rect);
    AddPrim(scratch->order_table + placement->z.w.i * 4,
                  prim);
    prim = packet + 0x58;
    PopMatrix();
    ((GpuContext *)*state_ptr)->packetCursor = prim;
    return 0;
}
