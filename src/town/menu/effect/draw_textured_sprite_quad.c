#include "shared/gpu_packets.h"
#include "town/menu/motion.h"
#include "town/menu/textured_sprite_quad_packets.h"
#include "common.h"
#include "shared/game_work.h"

   /* root in draw_textured_sprite_quad */


typedef struct S_800A17CC_2 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x59];
    s16 unk_6C;
    s16 unk_6E;
    u8 unk_70;
    u8 pad_71[0x1];
    u8 unk_72;
    u8 pad_73[0x5];
    u16 unk_78;
    s16 unk_7A;
} S_800A17CC_2;   /* arg0 in draw_textured_sprite_quad */



/* Projection work at 0x1F800000 for this textured-quad renderer. The
 * four world vertices feed RotTransPers4 and its four packed screen outputs. */
typedef struct TownQuadWork {
    u8 pad_00[0x24];
    u32 ordering_table;
    u8 pad_28[0x4C];
    struct { u16 x, y, z, pad; } corners[4];
    s32 depth_cue;
    u32 transform_flags;
    u8 pad_9C[0x28];
    s32 ordering_depth;
    u8 pad_C8[0x20];
    struct { u16 x, y; } screen[4];
} TownQuadWork;

typedef struct {} EmptyArg;

extern s32 RotTransPers4();
extern s32 GetTPage();
extern s32 GetClut();
extern void AddPrim();
extern void SetSemiTrans();
extern void SetPolyF4();
extern void SetPolyFT4();
extern void SetDrawMode();
struct MovingPosition; struct S_800A130C_0; void copy_odd_halfwords_3(struct S_800A130C_0 *, struct MovingPosition *);
struct S_800A1330_0; struct S_800A1330_1; void copy_menu_vector_halfwords(struct S_800A1330_0 *, struct S_800A1330_1 *);
extern s16 D_800D0A40;

/* Project and enqueue a textured sprite quad with a translucent overlay. */
void draw_textured_sprite_quad(void *sprite_arg, s32 position) {
    S_800A17CC_2 *sprite = sprite_arg;
    s16 texture_window[4];
    s32 texture_page;
    s32 texture_y;
    s32 height;
    register s32 top_z;
    GpuContext *render_state;
    POLY_FT4 *textured_quad;
    FlatOverlayQuadPacket *overlay_quad;
    u8 *draw_mode;
    EmptyArg unused_arg;
    void *screen_xy0;
    void *screen_xy1;
    void *screen_xy2;
    void *screen_xy3;
    void *depth_cue;
    void *transform_flags;
    void *vertex2;
    void *vertex3;
    s32 window_size;
    s32 color;
    POLY_FT4 *quad_packet;
    TownQuadWork *scratch;

    color = 0x800000;
    window_size = 0x80;
    texture_window[1] = 0;
    texture_window[0] = 0;
    texture_window[2] = window_size;
    texture_window[3] = window_size;

    {
        GpuContext *state = g_game_work.draw_buffer;

        textured_quad = state->packetCursor;
        quad_packet = textured_quad;
        state->packetCursor = (u8 *)textured_quad + 0x28;
    }
    color |= 0x8080;
    /* Retail fills the four RGB/code bytes with one packed word store. */
    *(s32 *)&textured_quad->r0 = color;
    SetPolyFT4(quad_packet);

    texture_page = GetTPage(1, 0,
        sprite->unk_6C & 0xFF80, sprite->unk_6E);
    textured_quad->tpage = texture_page;
    textured_quad->clut = GetClut(0, 0x1EF);

    {
        s32 texture_x;
        s32 left_u;

        texture_x = sprite->unk_6C;
        scratch = (TownQuadWork *)0x1F800000;
        left_u = (s16)(texture_x % 0x80);
        left_u /= 2;
        textured_quad->u2 = left_u;
        textured_quad->u0 = left_u;
    }
    {
        s32 texture_x;
        s16 page_x;
        s32 right_u;

        texture_x = sprite->unk_6C;
        page_x = texture_x % 0x80;
        right_u = (page_x / 2) + sprite->unk_70;
        textured_quad->u3 = right_u;
        textured_quad->u1 = right_u;
    }
    {
        s32 source_y;
        s32 top_v;

        source_y = sprite->unk_6E;
        top_v = source_y % 0x100;
        textured_quad->v1 = top_v;
        textured_quad->v0 = top_v;
    }

    texture_y = sprite->unk_6E;
    {
        s32 bottom_v;

        bottom_v = (texture_y % 0x100) + sprite->unk_72;
        textured_quad->v3 = bottom_v;
        textured_quad->v2 = bottom_v;
    }

    copy_odd_halfwords_3((void *)&scratch->corners[0], (struct MovingPosition *)(position));
    copy_odd_halfwords_3((void *)&scratch->corners[1], (struct MovingPosition *)(position));
    copy_odd_halfwords_3((void *)&scratch->corners[2], (struct MovingPosition *)(position));
    copy_menu_vector_halfwords((void *)&scratch->corners[3], (void *)&scratch->corners[0]);

    screen_xy0 = &scratch->screen[0];
    screen_xy1 = &scratch->screen[1];
    screen_xy2 = &scratch->screen[2];
    screen_xy3 = &scratch->screen[3];
    depth_cue = &scratch->depth_cue;
    transform_flags = &scratch->transform_flags;

    {
        s32 quad_y;

        quad_y = scratch->corners[3].y - 0x30;
        vertex2 = &scratch->corners[2];
        scratch->corners[3].y = quad_y;
        scratch->corners[2].y = quad_y;
        scratch->corners[1].y = quad_y;
        scratch->corners[0].y = quad_y;
    }
    {
        s32 left_x;

        left_x = scratch->corners[0].x - sprite->unk_78;
        scratch->corners[0].x = left_x;
        scratch->corners[2].x = left_x;
    }
    {
        s32 right_x;

        right_x = scratch->corners[1].x + sprite->unk_78;
        vertex3 = &scratch->corners[3];
        scratch->corners[1].x = right_x;
        scratch->corners[3].x = right_x;
    }
    height = sprite->unk_7A;
    scratch->ordering_depth = RotTransPers4(
        (void *)&scratch->corners[0], (void *)&scratch->corners[1],
        vertex2, vertex3,
        screen_xy0, screen_xy1, screen_xy2, screen_xy3, depth_cue, transform_flags,
        (top_z = scratch->corners[0].z - height * 2,
         scratch->corners[0].z = top_z,
         scratch->corners[1].z = top_z,
         unused_arg)) - 8;

    textured_quad->x0 = scratch->screen[0].x;
    textured_quad->y0 = scratch->screen[0].y;
    textured_quad->x1 = scratch->screen[1].x;
    textured_quad->y1 = scratch->screen[1].y;
    textured_quad->x2 = scratch->screen[2].x;
    textured_quad->y2 = scratch->screen[2].y;
    textured_quad->x3 = scratch->screen[3].x;
    textured_quad->y3 = scratch->screen[3].y;

    render_state = g_game_work.draw_buffer;
    overlay_quad = render_state->packetCursor;
    render_state->packetCursor = (u8 *)overlay_quad + 0x18;
    overlay_quad->red = sprite->unk_12;
    overlay_quad->green = sprite->unk_12;
    overlay_quad->blue = sprite->unk_12;
    SetPolyF4(overlay_quad);
    SetSemiTrans(overlay_quad, 1);
    overlay_quad->x0 = scratch->screen[0].x;
    overlay_quad->y0 = scratch->screen[0].y;
    overlay_quad->x1 = scratch->screen[1].x;
    overlay_quad->y1 = scratch->screen[1].y;
    overlay_quad->x2 = scratch->screen[2].x;
    overlay_quad->y2 = scratch->screen[2].y;
    overlay_quad->x3 = scratch->screen[3].x;
    overlay_quad->y3 = scratch->screen[3].y;

    render_state = g_game_work.draw_buffer;
    scratch->ordering_table = (s32)((u8 *)render_state + 0xB0);
    draw_mode = render_state->packetCursor;
    render_state->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0, texture_page & 0xFFFF, &D_800D0A40);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), overlay_quad);

    render_state = g_game_work.draw_buffer;
    draw_mode = render_state->packetCursor;
    render_state->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0,
        GetTPage(0, 1, 0x140, 0) & 0xFFFF, 0);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), textured_quad);

    render_state = g_game_work.draw_buffer;
    draw_mode = render_state->packetCursor;
    render_state->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0, texture_page & 0xFFFF, texture_window);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
}
