#include "shared/gpu_packets.h"
#include "town/menu/motion.h"
#include "common.h"
#include "shared/game_work.h"

   /* root in draw_textured_sprite_quad */

typedef struct S_800A17CC_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u16 unk_08;
    u16 unk_0A;
    s8 unk_0C;
    s8 unk_0D;
    s16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x2];
    u16 unk_20;
    u8 pad_22[0x2];
    s8 unk_24;
    s8 unk_25;
} S_800A17CC_1;   /* packet40 in draw_textured_sprite_quad */

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

typedef struct S_800A17CC_3 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 unk_0E;
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
} S_800A17CC_3;   /* packet24 in draw_textured_sprite_quad */


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
void draw_textured_sprite_quad(void *sprite, s32 position) {
    s16 texture_window[4];
    s32 texture_page;
    s32 texture_y;
    s32 height;
    register s32 top_z;
    u8 *render_state;
    u8 *textured_quad;
    u8 *overlay_quad;
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
    u8 *quad_packet;
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
        state->packetCursor = textured_quad + 0x28;
    }
    color |= 0x8080;
    ((S_800A17CC_1 *)textured_quad)->unk_04 = color;
    SetPolyFT4(quad_packet);

    texture_page = GetTPage(1, 0,
        ((S_800A17CC_2 *)sprite)->unk_6C & 0xFF80, ((S_800A17CC_2 *)sprite)->unk_6E);
    ((S_800A17CC_1 *)textured_quad)->unk_16 = texture_page;
    ((S_800A17CC_1 *)textured_quad)->unk_0E = GetClut(0, 0x1EF);

    {
        s32 texture_x;
        s32 left_u;

        texture_x = ((S_800A17CC_2 *)sprite)->unk_6C;
        scratch = (TownQuadWork *)0x1F800000;
        left_u = (s16)(texture_x % 0x80);
        left_u /= 2;
        ((S_800A17CC_1 *)textured_quad)->unk_1C = left_u;
        ((S_800A17CC_1 *)textured_quad)->unk_0C = left_u;
    }
    {
        s32 texture_x;
        s16 page_x;
        s32 right_u;

        texture_x = ((S_800A17CC_2 *)sprite)->unk_6C;
        page_x = texture_x % 0x80;
        right_u = (page_x / 2) + ((S_800A17CC_2 *)sprite)->unk_70;
        ((S_800A17CC_1 *)textured_quad)->unk_24 = right_u;
        ((S_800A17CC_1 *)textured_quad)->unk_14 = right_u;
    }
    {
        s32 source_y;
        s32 top_v;

        source_y = ((S_800A17CC_2 *)sprite)->unk_6E;
        top_v = source_y % 0x100;
        ((S_800A17CC_1 *)textured_quad)->unk_15 = top_v;
        ((S_800A17CC_1 *)textured_quad)->unk_0D = top_v;
    }

    texture_y = ((S_800A17CC_2 *)sprite)->unk_6E;
    {
        s32 bottom_v;

        bottom_v = (texture_y % 0x100) + ((S_800A17CC_2 *)sprite)->unk_72;
        ((S_800A17CC_1 *)textured_quad)->unk_25 = bottom_v;
        ((S_800A17CC_1 *)textured_quad)->unk_1D = bottom_v;
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

        left_x = scratch->corners[0].x - ((S_800A17CC_2 *)sprite)->unk_78;
        scratch->corners[0].x = left_x;
        scratch->corners[2].x = left_x;
    }
    {
        s32 right_x;

        right_x = scratch->corners[1].x + ((S_800A17CC_2 *)sprite)->unk_78;
        vertex3 = &scratch->corners[3];
        scratch->corners[1].x = right_x;
        scratch->corners[3].x = right_x;
    }
    height = ((S_800A17CC_2 *)sprite)->unk_7A;
    scratch->ordering_depth = RotTransPers4(
        (void *)&scratch->corners[0], (void *)&scratch->corners[1],
        vertex2, vertex3,
        screen_xy0, screen_xy1, screen_xy2, screen_xy3, depth_cue, transform_flags,
        (top_z = scratch->corners[0].z - height * 2,
         scratch->corners[0].z = top_z,
         scratch->corners[1].z = top_z,
         unused_arg)) - 8;

    ((S_800A17CC_1 *)textured_quad)->unk_08 = scratch->screen[0].x;
    ((S_800A17CC_1 *)textured_quad)->unk_0A = scratch->screen[0].y;
    ((S_800A17CC_1 *)textured_quad)->unk_10 = scratch->screen[1].x;
    ((S_800A17CC_1 *)textured_quad)->unk_12 = scratch->screen[1].y;
    ((S_800A17CC_1 *)textured_quad)->unk_18 = scratch->screen[2].x;
    ((S_800A17CC_1 *)textured_quad)->unk_1A = scratch->screen[2].y;
    ((S_800A17CC_1 *)textured_quad)->unk_20 = scratch->screen[3].x;
    (*(u16 *)((u8 *)textured_quad + 0x22)) = scratch->screen[3].y;

    render_state = g_game_work.draw_buffer;
    overlay_quad = ((GpuContext *)render_state)->packetCursor;
    ((GpuContext *)render_state)->packetCursor = overlay_quad + 0x18;
    ((S_800A17CC_3 *)overlay_quad)->unk_04 = ((S_800A17CC_2 *)sprite)->unk_12;
    ((S_800A17CC_3 *)overlay_quad)->unk_05 = ((S_800A17CC_2 *)sprite)->unk_12;
    ((S_800A17CC_3 *)overlay_quad)->unk_06 = ((S_800A17CC_2 *)sprite)->unk_12;
    SetPolyF4(overlay_quad);
    SetSemiTrans(overlay_quad, 1);
    ((S_800A17CC_3 *)overlay_quad)->unk_08 = scratch->screen[0].x;
    ((S_800A17CC_3 *)overlay_quad)->unk_0A = scratch->screen[0].y;
    ((S_800A17CC_3 *)overlay_quad)->unk_0C = scratch->screen[1].x;
    ((S_800A17CC_3 *)overlay_quad)->unk_0E = scratch->screen[1].y;
    ((S_800A17CC_3 *)overlay_quad)->unk_10 = scratch->screen[2].x;
    ((S_800A17CC_3 *)overlay_quad)->unk_12 = scratch->screen[2].y;
    ((S_800A17CC_3 *)overlay_quad)->unk_14 = scratch->screen[3].x;
    (*(u16 *)((u8 *)overlay_quad + 0x16)) = scratch->screen[3].y;

    render_state = g_game_work.draw_buffer;
    scratch->ordering_table = (s32)(render_state + 0xB0);
    draw_mode = ((GpuContext *)render_state)->packetCursor;
    ((GpuContext *)render_state)->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0, texture_page & 0xFFFF, &D_800D0A40);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), overlay_quad);

    render_state = g_game_work.draw_buffer;
    draw_mode = ((GpuContext *)render_state)->packetCursor;
    ((GpuContext *)render_state)->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0,
        GetTPage(0, 1, 0x140, 0) & 0xFFFF, 0);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), textured_quad);

    render_state = g_game_work.draw_buffer;
    draw_mode = ((GpuContext *)render_state)->packetCursor;
    ((GpuContext *)render_state)->packetCursor = draw_mode + 0xC;
    SetDrawMode(draw_mode, 1, 0, texture_page & 0xFFFF, texture_window);
    AddPrim((u8 *)scratch->ordering_table + (scratch->ordering_depth * 4), draw_mode);
}
