#include "common.h"

typedef struct S_800A17CC_0 {
    u8 pad_00[0x8D0];
    u8 * unk_8D0;
} S_800A17CC_0;   /* root in func_800A17CC */

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
} S_800A17CC_1;   /* packet40 in func_800A17CC */

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
} S_800A17CC_2;   /* arg0 in func_800A17CC */

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
} S_800A17CC_3;   /* packet24 in func_800A17CC */


#define SCRATCH(type, offset) (*(type *)((u8 *)scratch + (offset)))
#define VSCRATCH(type, offset) (*(volatile type *)((u8 *)scratch + (offset)))

typedef struct {} EmptyArg;

extern s32 func_800654B0();
extern s32 func_80066460();
extern s32 func_8006649C();
extern void func_8006658C();
extern void func_80066640();
extern void func_800666E0();
extern void func_800666F4();
extern void func_80067F20();
extern void func_800A130C();
extern void func_800A1330();
extern u8 *D_80083160;
extern u8 D_1F800000[];
extern s16 D_800D0A40;

/* Project and enqueue a textured sprite quad with a translucent overlay. */
void func_800A17CC(void *sprite, s32 position) {
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
    register u8 *scratch ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */

    color = 0x800000;
    ASM_KEEP_NV(color);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    render_state = D_80083160;
    window_size = 0x80;
    texture_window[1] = 0;
    texture_window[0] = 0;
    texture_window[2] = window_size;
    texture_window[3] = window_size;

    textured_quad = ((S_800A17CC_0 *)render_state)->unk_8D0;
    quad_packet = textured_quad;
    ((S_800A17CC_0 *)render_state)->unk_8D0 = textured_quad + 0x28;
    color |= 0x8080;
    ((S_800A17CC_1 *)textured_quad)->unk_04 = color;
    func_800666F4(quad_packet, color);

    texture_page = func_80066460(1, 0,
        ((S_800A17CC_2 *)sprite)->unk_6C & 0xFF80, ((S_800A17CC_2 *)sprite)->unk_6E);
    ((S_800A17CC_1 *)textured_quad)->unk_16 = texture_page;
    ((S_800A17CC_1 *)textured_quad)->unk_0E = func_8006649C(0, 0x1EF);

    {
        s32 texture_x;
        s32 left_u;

        texture_x = ((S_800A17CC_2 *)sprite)->unk_6C;
        ASM_KEEP_NV(texture_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        scratch = (u8 *)0x1F800000;
        ASM_KEEP(scratch);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
        s32 texture_y;
        s32 top_v;

        texture_y = ((S_800A17CC_2 *)sprite)->unk_6E;
        top_v = texture_y % 0x100;
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

    func_800A130C((void *)0x1F800074, position, texture_y);
    func_800A130C((void *)0x1F80007C, position);
    func_800A130C((void *)0x1F800084, position);
    func_800A1330((void *)0x1F80008C, (void *)0x1F800074);

    screen_xy0 = (void *)0x1F8000E8;
    screen_xy1 = (void *)0x1F8000EC;
    screen_xy2 = (void *)0x1F8000F0;
    screen_xy3 = (void *)0x1F8000F4;
    depth_cue = (void *)0x1F800094;
    transform_flags = (void *)0x1F800098;

    {
        s32 quad_y;

        quad_y = SCRATCH(u16, 0x8E) - 0x30;
        vertex2 = (void *)0x1F800084;
        SCRATCH(u16, 0x8E) = quad_y;
        SCRATCH(u16, 0x86) = quad_y;
        SCRATCH(u16, 0x7E) = quad_y;
        SCRATCH(u16, 0x76) = quad_y;
    }
    {
        s32 left_x;

        left_x = SCRATCH(u16, 0x74) - ((S_800A17CC_2 *)sprite)->unk_78;
        SCRATCH(u16, 0x74) = left_x;
        SCRATCH(u16, 0x84) = left_x;
    }
    {
        s32 right_x;

        right_x = SCRATCH(u16, 0x7C) + ((S_800A17CC_2 *)sprite)->unk_78;
        vertex3 = (void *)0x1F80008C;
        SCRATCH(u16, 0x7C) = right_x;
        SCRATCH(u16, 0x8C) = right_x;
    }
    height = ((S_800A17CC_2 *)sprite)->unk_7A;
    SCRATCH(s32, 0xC4) = func_800654B0(
        (void *)0x1F800074, (void *)0x1F80007C,
        vertex2, vertex3,
        screen_xy0, screen_xy1, screen_xy2, screen_xy3, depth_cue, transform_flags,
        (top_z = SCRATCH(u16, 0x78),
            height *= 2,
            top_z -= height,
            SCRATCH(u16, 0x78) = top_z,
            SCRATCH(u16, 0x80) = top_z,
            unused_arg)) - 8;

    ((S_800A17CC_1 *)textured_quad)->unk_08 = SCRATCH(u16, 0xE8);
    ((S_800A17CC_1 *)textured_quad)->unk_0A = SCRATCH(u16, 0xEA);
    ((S_800A17CC_1 *)textured_quad)->unk_10 = SCRATCH(u16, 0xEC);
    ((S_800A17CC_1 *)textured_quad)->unk_12 = SCRATCH(u16, 0xEE);
    ((S_800A17CC_1 *)textured_quad)->unk_18 = SCRATCH(u16, 0xF0);
    ((S_800A17CC_1 *)textured_quad)->unk_1A = SCRATCH(u16, 0xF2);
    ((S_800A17CC_1 *)textured_quad)->unk_20 = SCRATCH(u16, 0xF4);
    (*(u16 *)((u8 *)textured_quad + 0x22)) = SCRATCH(u16, 0xF6);

    render_state = D_80083160;
    overlay_quad = ((S_800A17CC_0 *)render_state)->unk_8D0;
    ((S_800A17CC_0 *)render_state)->unk_8D0 = overlay_quad + 0x18;
    ((S_800A17CC_3 *)overlay_quad)->unk_04 = ((S_800A17CC_2 *)sprite)->unk_12;
    ((S_800A17CC_3 *)overlay_quad)->unk_05 = ((S_800A17CC_2 *)sprite)->unk_12;
    ((S_800A17CC_3 *)overlay_quad)->unk_06 = ((S_800A17CC_2 *)sprite)->unk_12;
    func_800666E0(overlay_quad);
    func_80066640(overlay_quad, 1);
    ((S_800A17CC_3 *)overlay_quad)->unk_08 = SCRATCH(u16, 0xE8);
    ((S_800A17CC_3 *)overlay_quad)->unk_0A = SCRATCH(u16, 0xEA);
    ((S_800A17CC_3 *)overlay_quad)->unk_0C = SCRATCH(u16, 0xEC);
    ((S_800A17CC_3 *)overlay_quad)->unk_0E = SCRATCH(u16, 0xEE);
    ((S_800A17CC_3 *)overlay_quad)->unk_10 = SCRATCH(u16, 0xF0);
    ((S_800A17CC_3 *)overlay_quad)->unk_12 = SCRATCH(u16, 0xF2);
    ((S_800A17CC_3 *)overlay_quad)->unk_14 = SCRATCH(u16, 0xF4);
    (*(u16 *)((u8 *)overlay_quad + 0x16)) = SCRATCH(u16, 0xF6);

    render_state = D_80083160;
    SCRATCH(u32, 0x24) = (s32)(render_state + 0xB0);
    draw_mode = ((S_800A17CC_0 *)render_state)->unk_8D0;
    ((S_800A17CC_0 *)render_state)->unk_8D0 = draw_mode + 0xC;
    func_80067F20(draw_mode, 1, 0, texture_page & 0xFFFF, &D_800D0A40);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), draw_mode);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), overlay_quad);

    render_state = D_80083160;
    draw_mode = ((S_800A17CC_0 *)render_state)->unk_8D0;
    ((S_800A17CC_0 *)render_state)->unk_8D0 = draw_mode + 0xC;
    func_80067F20(draw_mode, 1, 0,
        func_80066460(0, 1, 0x140, 0) & 0xFFFF, 0);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), draw_mode);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), textured_quad);

    render_state = D_80083160;
    draw_mode = ((S_800A17CC_0 *)render_state)->unk_8D0;
    ((S_800A17CC_0 *)render_state)->unk_8D0 = draw_mode + 0xC;
    func_80067F20(draw_mode, 1, 0, texture_page & 0xFFFF, texture_window);
    func_8006658C((u8 *)SCRATCH(u32, 0x24) + (SCRATCH(s32, 0xC4) * 4), draw_mode);
}
