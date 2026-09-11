#include "common.h"

typedef struct S_800CF8E4_0 {
    void * unk_00;
    u8 pad_04[0x1A];
    s16 unk_1E;
    u8 pad_20[0x1BC];
    s32 unk_1DC;
} S_800CF8E4_0;   /* var_s6 in func_800CF8E4 */

typedef struct S_800CF8E4_1 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800CF8E4_1;   /* temp_s5 in func_800CF8E4 */

typedef struct S_800CF8E4_2 {
    u8 pad_00[0x8];
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x2];
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x2];
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    u16 unk_28;
    u16 unk_2A;
    u16 unk_2C;
    u8 pad_2E[0x56];
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    s32 unk_90;
    u8 pad_94[0x10];
    u16 unk_A4;
    u16 unk_A6;
    u16 unk_A8;
} S_800CF8E4_2;   /* temp_s1 in func_800CF8E4 */

typedef struct S_800CF8E4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_3;   /* (void *)init_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_4 {
    u8 pad_00[0x34];
    s32 unk_34;
    s32 unk_38;
} S_800CF8E4_4;   /* var_a0 in func_800CF8E4 */

typedef struct S_800CF8E4_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
    s32 unk_3C;
} S_800CF8E4_5;   /* var_a1 in func_800CF8E4 */

typedef struct S_800CF8E4_6 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u16 unk_06;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800CF8E4_6;   /* temp_t0_2 in func_800CF8E4 */

typedef struct S_800CF8E4_7 {
    s32 unk_00;
    u16 unk_04;
} S_800CF8E4_7;   /* (void *)geom_v0 in func_800CF8E4 */

typedef struct S_800CF8E4_8 {
    s32 unk_00;
    s16 unk_04;
} S_800CF8E4_8;   /* temp_v1_11 in func_800CF8E4 */

typedef struct S_800CF8E4_9_pre {
    s8 unk_00;
    u8 pad_01[0x3];
} S_800CF8E4_9_pre;   /* the 0x4 bytes before var_a3 in func_800CF8E4, addressed as var_a3[-1] */

typedef struct S_800CF8E4_9 {
    u8 unk_00;
} S_800CF8E4_9;   /* var_a3 in func_800CF8E4 */

typedef struct S_800CF8E4_10 {
    u8 pad_00[0x4];
    s16 unk_04;
} S_800CF8E4_10;   /* ((*(u16 *)(ram_base + 0x170) * 8) + temp_s4) in func_800CF8E4 */

typedef struct S_800CF8E4_11 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0xC];
    s32 unk_38;
} S_800CF8E4_11;   /* var_v1 in func_800CF8E4 */

typedef struct S_800CF8E4_12 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_800CF8E4_12;   /* ((((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2) in func_800CF8E4 */

typedef struct S_800CF8E4_13 {
    s32 unk_00;
} S_800CF8E4_13;   /* (((S_800CF8E4_6 *)temp_t0_2)->unk_06 * 8) + temp_s2 in func_800CF8E4 */

typedef struct S_800CF8E4_14 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800CF8E4_14;   /* ((S_800CF8E4_0 *)var_s6)->unk_00 in func_800CF8E4 */


typedef struct {
    u16 index;
    s16 offset;
    u16 flags;
} CellRec;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

s32 func_80046884();
s32 func_80046C20();
s32 func_80064624();
s32 func_80064D20();
s32 func_80064D50();
s16 func_800BCB04();
extern s32 D_80013180[0x2000];
extern u16 D_80013714[0x1000];
extern void *D_80083160[0x1000];
extern s32 D_800DCF58[0x100];

/* Render visible dungeon cells as lit, textured polygons in the ordering table. */
void func_800CF8E4(void) {
    register u8 *ram_base ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u16 view_corners[23];
    s32 *ot_entry;
    s32 neighbor_index;
    u8 *vertices;
    CellRec *cells;
    register u8 *normals ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 render_flags;
    s32 row_step;
    s32 face_skip;
    s32 min_x;
    s32 max_x;
    s32 next_column;
    s32 next_x;
    s32 edge_remaining;
    s32 coord;
    s32 normal_xy;
    s32 occlusion_height;
    s32 quad_depth;
    s32 view_height;
    s32 edge_x;
    s32 scan_x;
    s32 scan_y;
    s32 map_width;
    s32 cell_index;
    s32 overlay_color;
    s32 *overlay_ot_entry;
    u16 normal_x;
    u16 normal_y;
    s32 normal_index;
    u16 neighbor_flags;
    u16 corner_0_x;
    u16 corner_0_y;
    u16 corner_0_z;
    u16 corner_1_x;
    u16 corner_1_y;
    u16 corner_1_z;
    u16 corner_2_x;
    u16 corner_2_y;
    u16 corner_2_z;
    u16 corner_3_x;
    u16 corner_3_y;
    u16 corner_3_z;
    u8 *reset_page;
    u8 neighbor_face_flags;
    s32 face_flags;
    register u8 *view ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    u8 *packet;
    u8 *map;
    u8 *scene;
    void *face;
    void *normal;
    CellRec *cell;
    CellRec *neighbor;
    void *edge_start;
    void *packet_addr;
    void *edge;
    void *packet_code;
    void *edge_end;
    void *render_input;
    register void *render_output ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 render_arg ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 minus_one;

    scene = (u8 *)D_80083160;
    render_flags = D_80013714[0];
    ram_base = (u8 *)0x1F800000;
    view = scene + 0x18;
    map = scene + 0x1DC;
    cells = (CellRec *)((S_800CF8E4_0 *)scene)->unk_1DC;
    vertices = (u8 *)((S_800CF8E4_1 *)map)->unk_08;
    normals = (u8 *)((S_800CF8E4_1 *)map)->unk_0C;
    if (!(render_flags & 2)) {
        coord = func_800BCB04(((S_800CF8E4_2 *)view)->unk_A4, ((S_800CF8E4_2 *)view)->unk_A6, (s16) (((S_800CF8E4_2 *)view)->unk_A8 - 0x20));
        if (coord < 0x201) {
            *(s32 *)(ram_base + 0x158) = coord;
            goto L_CF974;
        }
        *(s32 *)(ram_base + 0x158) = 0;
L_CF974:
        func_80064D50(((void **)((s8 *)((void **)((s8 *)view + 0x58)))));
        func_80064624(((S_800CF8E4_2 *)view)->unk_84, ((S_800CF8E4_2 *)view)->unk_88);
        func_80064D20(((void **)((s8 *)((void **)((s8 *)view + 0x38)))));
        render_input = view;
        ASM_KEEP(render_input);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        render_output = view_corners;
        render_arg = *(s32 *)(ram_base + 0x158);
        ((S_800CF8E4_0 *)scene)->unk_1E = 0x1BA;
        func_80046884(render_input, render_output, render_arg);
        reset_page = (u8 *)0x800E0000;
        if (reset_page[-0x30A8] != 0) {
            corner_0_x = view_corners[0];
            corner_0_y = view_corners[1];
            corner_0_z = view_corners[2];
            corner_1_x = ((S_800CF8E4_2 *)view)->unk_10;
            corner_1_y = ((S_800CF8E4_2 *)view)->unk_12;
            corner_1_z = ((S_800CF8E4_2 *)view)->unk_14;
            corner_2_x = ((S_800CF8E4_2 *)view)->unk_18;
            corner_2_y = ((S_800CF8E4_2 *)view)->unk_1A;
            corner_2_z = ((S_800CF8E4_2 *)view)->unk_1C;
            corner_3_x = ((S_800CF8E4_2 *)view)->unk_20;
            corner_3_y = ((S_800CF8E4_2 *)view)->unk_22;
            corner_3_z = ((S_800CF8E4_2 *)view)->unk_24;
            reset_page[-0x30A8] = 0;
            ((S_800CF8E4_2 *)view)->unk_08 = corner_0_x;
            ((S_800CF8E4_2 *)view)->unk_28 = corner_0_x;
            ((S_800CF8E4_2 *)view)->unk_0A = corner_0_y;
            ((S_800CF8E4_2 *)view)->unk_0C = corner_0_z;
            ((S_800CF8E4_2 *)view)->unk_2C = corner_0_z;
            ((S_800CF8E4_2 *)view)->unk_10 = corner_1_x;
            ((S_800CF8E4_2 *)view)->unk_12 = corner_1_y;
            ((S_800CF8E4_2 *)view)->unk_14 = corner_1_z;
            ((S_800CF8E4_2 *)view)->unk_18 = corner_2_x;
            ((S_800CF8E4_2 *)view)->unk_1A = corner_2_y;
            ((S_800CF8E4_2 *)view)->unk_1C = corner_2_z;
            ((S_800CF8E4_2 *)view)->unk_20 = corner_3_x;
            ((S_800CF8E4_2 *)view)->unk_22 = corner_3_y;
            ((S_800CF8E4_2 *)view)->unk_24 = corner_3_z;
            goto L_CFB98;
        }
        {
            s32 blended_coord;
            s32 coord_delta;
            s32 next_delta;
            s32 old_coord;
            register s32 closing_z ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            coord_delta = (s16)view_corners[0];
            blended_coord = (s16)((S_800CF8E4_2 *)view)->unk_08;
            next_delta = (s16)view_corners[1];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_0A;
            coord_delta -= blended_coord;
            coord_delta >>= 1;
            next_delta -= old_coord;
            next_delta >>= 1;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_08;
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_0C;
            blended_coord += coord_delta;
            ((S_800CF8E4_2 *)view)->unk_08 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_0A;
            coord_delta = (s16)view_corners[2];
            blended_coord += next_delta;
            coord_delta -= old_coord;
            coord_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_0A = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_0C;
            next_delta = (s16)view_corners[4];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_10;
            blended_coord += coord_delta;
            next_delta -= old_coord;
            next_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_0C = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_10;
            coord_delta = (s16)view_corners[5];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_12;
            blended_coord += next_delta;
            coord_delta -= old_coord;
            coord_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_10 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_12;
            next_delta = (s16)view_corners[6];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_14;
            blended_coord += coord_delta;
            next_delta -= old_coord;
            next_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_12 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_14;
            coord_delta = (s16)view_corners[8];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_18;
            blended_coord += next_delta;
            coord_delta -= old_coord;
            coord_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_14 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_18;
            next_delta = (s16)view_corners[9];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_1A;
            blended_coord += coord_delta;
            next_delta -= old_coord;
            next_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_18 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_1A;
            coord_delta = (s16)view_corners[10];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_1C;
            blended_coord += next_delta;
            coord_delta -= old_coord;
            ((S_800CF8E4_2 *)view)->unk_1A = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_1C;
            coord_delta >>= 1;
            blended_coord += coord_delta;
            do {
                ((S_800CF8E4_2 *)view)->unk_1C = (u16)blended_coord;
            } while (0);
            coord_delta = (s16)view_corners[12];
            blended_coord = (s16)((S_800CF8E4_2 *)view)->unk_20;
            next_delta = (s16)view_corners[13];
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_22;
            closing_z = ((S_800CF8E4_2 *)view)->unk_0C;
            coord_delta -= blended_coord;
            coord_delta >>= 1;
            next_delta -= old_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_20;
            old_coord = (s16)((S_800CF8E4_2 *)view)->unk_24;
            blended_coord += coord_delta;
            ((S_800CF8E4_2 *)view)->unk_20 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_22;
            coord_delta = (s16)view_corners[14];
            next_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_2C = (u16)closing_z;
            blended_coord += next_delta;
            coord_delta -= old_coord;
            coord_delta >>= 1;
            ((S_800CF8E4_2 *)view)->unk_22 = (u16)blended_coord;
            blended_coord = ((S_800CF8E4_2 *)view)->unk_24;
            next_delta = ((S_800CF8E4_2 *)view)->unk_08;
            old_coord = ((S_800CF8E4_2 *)view)->unk_0A;
            blended_coord += coord_delta;
            ((S_800CF8E4_2 *)view)->unk_24 = (u16)blended_coord;
            ((S_800CF8E4_2 *)view)->unk_28 = (u16)next_delta;
            ((S_800CF8E4_2 *)view)->unk_2A = (u16)old_coord;
        }
L_CFB98:
        {
            s32 setup_value;
            s32 setup_base;
            s32 width_shift_or_end;
            register s32 height_shift ASM_REG("$8");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 column_mask ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 row_mask ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 base_color ASM_REG("$11");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            register s32 draw_mode ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            render_input = view + 8;
            render_output = ram_base + 0x01C;
            setup_value = ((S_800CF8E4_2 *)view)->unk_90;
            render_arg = (s32)(ram_base + 0x174);
            *(s32 *)(ram_base + 0x000) = setup_value;
            setup_value = (s32)0x80010000;
            setup_base = (s32)((S_800CF8E4_0 *)scene)->unk_00;
            width_shift_or_end = ((S_800CF8E4_1 *)map)->unk_14;
            height_shift = ((S_800CF8E4_1 *)map)->unk_16;
            column_mask = ((S_800CF8E4_1 *)map)->unk_18;
            row_mask = ((S_800CF8E4_1 *)map)->unk_1A;
            ASM_KEEP4(width_shift_or_end, height_shift, column_mask, row_mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            base_color = *(s32 *)(setup_value + 0x3180);
            draw_mode = *(u8 *)(setup_value + 0x3184);
            setup_value = *(u8 *)(setup_value + 0x3185);
            setup_base += 0xB8;
            do {
                *(s32 *)(ram_base + 0x124) = width_shift_or_end;
            } while (0);
            *(u16 *)(ram_base + 0x178) = (u16)setup_value;
            setup_value = width_shift_or_end;
            ASM_KEEP(setup_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            *(s32 *)(ram_base + 0x0BC) = setup_base;
            setup_base = 0x40;
            setup_value = setup_base << setup_value;
            *(s32 *)(ram_base + 0x128) = height_shift;
            *(s32 *)(ram_base + 0x114) = setup_value;
            do {
                setup_value = height_shift;
            } while (0);
            ASM_KEEP(setup_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            setup_base <<= setup_value;
            *(s32 *)(ram_base + 0x11C) = column_mask;
            *(s32 *)(ram_base + 0x120) = row_mask;
            *(s32 *)(ram_base + 0x110) = base_color;
            *(u16 *)(ram_base + 0x176) = (u16)draw_mode;
            width_shift_or_end = (s32)((S_800CF8E4_0 *)scene)->unk_00;
            setup_value = 0xAF3A;
            *(s32 *)(ram_base + 0x118) = setup_base;
            packet = (u8 *)((S_800CF8E4_3 *)((void *)width_shift_or_end))->unk_8D0;
            width_shift_or_end += setup_value;
            setup_value = 0xFFFF;
            *(s32 *)(ram_base + 0x14C) = setup_value;
            *(s32 *)(ram_base + 0x17C) = width_shift_or_end;
            *(u16 *)(ram_base + 0x174) = 4U;
            *(s32 *)(ram_base + 0x00C) = (s16)func_80046C20(render_input, render_output, render_arg, (void *)width_shift_or_end);
        }
        if (*(u16 *)(ram_base + 0x174) != 0) {
            s32 address_mask;
            register s32 one ASM_REG("$10");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 max_height;
            register s32 tag_mask ASM_REG("$13");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            one = 1;
            max_height = 0x7FFF;
            address_mask = 0xFFFFFF;
            tag_mask = (s32)0xFF000000;
loop_9:
            render_arg = 3;
            edge_start = (s32 *)(ram_base + 0x78);
            do {
                ASM_KEEP(edge_start);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                if (((S_800CF8E4_4 *)edge_start)->unk_38 == 0) {
                    s32 edge_start_y;
                    s32 current_y;

                    edge_start_y = ((S_800CF8E4_4 *)edge_start)->unk_34;
                    current_y = *(s32 *)(ram_base + 0x00C);
                    if (current_y >= edge_start_y) {
                        ((S_800CF8E4_4 *)edge_start)->unk_38 = one;
                    }
                }
                render_arg -= 1;
                edge_start -= 0x28;
            } while (render_arg >= 0);
            render_arg = 3;
            edge = (s32 *)(ram_base + 0x78);
            *(s32 *)(ram_base + 0x014) = max_height;
            *(s32 *)(ram_base + 0x018) = -0x7FFF;
loop_15:
            if (((S_800CF8E4_5 *)edge)->unk_38 > 0) {
                coord = ((S_800CF8E4_5 *)edge)->unk_1C;
                *(s32 *)(ram_base + 0x008) = coord;
                if (coord < *(s32 *)(ram_base + 0x014)) {
                    *(s32 *)(ram_base + 0x014) = coord;
                    goto L_CFCFC;
                }
                if (*(s32 *)(ram_base + 0x018) < coord) {
                    *(s32 *)(ram_base + 0x018) = coord;
                }
L_CFCFC:
                {
                    s32 edge_error;
                    register s32 edge_progress ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                    register s32 error_step ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

                    edge_progress = ((S_800CF8E4_5 *)edge)->unk_2C;
                    edge_error = ((S_800CF8E4_5 *)edge)->unk_24;
                    edge_progress += edge_error;
                    ((S_800CF8E4_5 *)edge)->unk_2C = edge_progress;
                    if (edge_progress >= 0) {
loop_22:
                        edge_progress = ((S_800CF8E4_5 *)edge)->unk_1C;
                        edge_error = ((S_800CF8E4_5 *)edge)->unk_30;
                        error_step = ((S_800CF8E4_5 *)edge)->unk_20;
                        edge_progress += edge_error;
                        edge_error = ((S_800CF8E4_5 *)edge)->unk_2C;
                        ((S_800CF8E4_5 *)edge)->unk_1C = edge_progress;
                        edge_progress = ((S_800CF8E4_5 *)edge)->unk_3C;
                        edge_error -= error_step;
                        edge_progress -= 0x40;
                        ((S_800CF8E4_5 *)edge)->unk_2C = edge_error;
                        ((S_800CF8E4_5 *)edge)->unk_3C = edge_progress;
                        if ((edge_progress > 0) && (edge_error >= 0)) {
                            goto loop_22;
                        }
                    }
                }
                edge_x = ((S_800CF8E4_5 *)edge)->unk_1C;
                *(s32 *)(ram_base + 0x008) = edge_x;
                if (edge_x < *(s32 *)(ram_base + 0x014)) {
                    *(s32 *)(ram_base + 0x014) = edge_x;
                }
                scan_x = *(s32 *)(ram_base + 0x008);
                if (*(s32 *)(ram_base + 0x018) < scan_x) {
                    *(s32 *)(ram_base + 0x018) = scan_x;
                }
                goto block_28;
            }
block_28:
            render_arg -= 1;
            edge -= 0x28;
            if (render_arg < 0) {
                scan_y = *(s32 *)(ram_base + 0x00C);
                if ((scan_y >= 0) && (*(s32 *)(ram_base + 0x118) >= scan_y)) {
                    min_x = (*(s32 *)(ram_base + 0x014) - 0x20) & ~0x3F;
                    *(s32 *)(ram_base + 0x014) = min_x;
                    if (min_x < 0) {
                        *(s32 *)(ram_base + 0x014) = 0;
                    }
                    map_width = *(s32 *)(ram_base + 0x114);
                    max_x = (*(s32 *)(ram_base + 0x018) + 0x20) & ~0x3F;
                    *(s32 *)(ram_base + 0x018) = max_x;
                    if (map_width < max_x) {
                        *(s32 *)(ram_base + 0x018) = map_width;
                    }
                    *(s32 *)(ram_base + 0x138) = (((u32) *(s32 *)(ram_base + 0x00C) >> 6) & *(s32 *)(ram_base + 0x120)) << *(s32 *)(ram_base + 0x124);
                    *(s32 *)(ram_base + 0x134) = ((u32) *(s32 *)(ram_base + 0x014) >> 6) & *(s32 *)(ram_base + 0x11C);
                    if (*(s32 *)(ram_base + 0x018) >= *(s32 *)(ram_base + 0x014)) {
loop_36:
                        cell_index = *(s32 *)(ram_base + 0x138) + *(s32 *)(ram_base + 0x134);
                        *(s32 *)(ram_base + 0x144) = cell_index;
                        cell = (CellRec *)((cell_index * 6) + (s32)cells);
                        packet_code = packet + 7;
                        if (cell->index != 0) {
                            *(s32 *)(ram_base + 0x12C) = (s32) cell->offset;
                            face = ((void **)((S_800CF8E4_1 *)map)->unk_04)[cells[*(s32 *)(ram_base + 0x144)].index];
L_CFE98:
                            {
                                register s32 vertex_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                                s32 vertex_offset;
                                s32 vertex_xy;
                                u16 cell_x;
                                register u16 vertex_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                                register u16 third_x ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */

                                vertex_value = ((S_800CF8E4_6 *)face)->unk_10;
                                cell_x = *(volatile u16 *)(ram_base + 0x014);
                                *(volatile s32 *)(ram_base + 0x170) = vertex_value;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_00;
                                vertex_offset = ((S_800CF8E4_6 *)face)->unk_14;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                *(volatile s32 *)(ram_base + 0x16C) = vertex_offset;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                vertex_offset = *(volatile u16 *)(ram_base + 0x12C);
                                *(volatile s32 *)(ram_base + 0x164) = vertex_value;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_00;
                                vertex_x = *(volatile u16 *)(ram_base + 0x164);
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy = cell_x + vertex_x;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                *(volatile u16 *)(ram_base + 0x0E4) = (u16)vertex_value;
                                vertex_value = *(volatile u16 *)(ram_base + 0x166);
                                vertex_offset = *(volatile s32 *)(ram_base + 0x00C);
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_02;
                                vertex_xy |= vertex_offset;
                                *(volatile s32 *)(ram_base + 0x0E0) = vertex_xy;

                                cell_x = *(volatile u16 *)(ram_base + 0x014);
                                vertex_offset = *(volatile u16 *)(ram_base + 0x12C);
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                *(volatile s32 *)(ram_base + 0x164) = vertex_value;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_02;
                                vertex_x = *(volatile u16 *)(ram_base + 0x164);
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_xy = cell_x + vertex_x;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_xy &= 0xFFFF;
                                vertex_value -= vertex_offset;
                                *(volatile u16 *)(ram_base + 0x0EC) = (u16)vertex_value;
                                vertex_value = *(volatile u16 *)(ram_base + 0x166);
                                vertex_offset = *(volatile s32 *)(ram_base + 0x00C);
                                vertex_value = (s16)vertex_value;
                                vertex_offset += vertex_value;
                                vertex_offset <<= 16;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_04;
                                vertex_xy |= vertex_offset;
                                *(volatile s32 *)(ram_base + 0x0E8) = vertex_xy;

                                cell_x = *(volatile u16 *)(ram_base + 0x014);
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_value = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_00;
                                *(volatile s32 *)(ram_base + 0x164) = vertex_value;
                                third_x = *(volatile u16 *)(ram_base + 0x164);
                                vertex_offset = *(volatile u16 *)(ram_base + 0x166);
                                vertex_xy = cell_x + third_x;
                                vertex_xy &= 0xFFFF;
                                vertex_offset = (s16)vertex_offset;
                                vertex_value = *(volatile s32 *)(ram_base + 0x00C);
                                vertex_value += vertex_offset;
                                vertex_value <<= 16;
                                vertex_xy |= vertex_value;
                                *(volatile s32 *)(ram_base + 0x0F0) = vertex_xy;
                                vertex_value = ((S_800CF8E4_6 *)face)->unk_04;
                                vertex_value <<= 3;
                                vertex_value += (s32)vertices;
                                vertex_offset = ((S_800CF8E4_7 *)((void *)vertex_value))->unk_04;
                                vertex_value = *(volatile u16 *)(ram_base + 0x12C);
                                vertex_offset -= vertex_value;
                                *(volatile u16 *)(ram_base + 0x0F4) = (u16)vertex_offset;
                            }
                            gte_ldv3(ram_base + 0xE0, ram_base + 0xE8, ram_base + 0xF0);
                            {
                                register s32 corner_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                                s32 cell_height;

                                corner_height = ((S_800CF8E4_12 *)(((((S_800CF8E4_6 *)face)->unk_06 * 8) + vertices)))->unk_04;
                                cell_height = *(volatile u16 *)(ram_base + 0x12C);
                                corner_height -= cell_height;
                                *(u16 *)(ram_base + 0x0FC) = (u16) corner_height;
                            }
                            gte_rtpt_nn();
                            gte_nclip();
                            gte_stopz(ram_base + 0xDC);
                            if (*(s32 *)(ram_base + 0x0DC) >= 0) {
                                gte_stflg(ram_base + 0xD8);
                                if (*(s32 *)(ram_base + 0x0D8) == 0) {
                                    gte_stsxy3_g3(packet);
                                    gte_avsz3();
                                    gte_stotz(ram_base + 0xC8);
                                    normal_index = *(u16 *)(ram_base + 0x170);
                                    if (*(s32 *)(ram_base + 0x14C) != normal_index) {
                                        *(s32 *)(ram_base + 0x14C) = (s32) normal_index;
                                        normal = (void *)((normal_index * 8) + (s32)normals);
                                        if (((S_800CF8E4_8 *)normal)->unk_04 >= 0) {
                                            normal_xy = ((S_800CF8E4_8 *)normal)->unk_00;
                                            if (!(normal_xy & 0x0FFF0FFF)) {
                                                *(s32 *)(ram_base + 0x010) = normal_xy;
                                                normal_x = *(u16 *)(ram_base + 0x010);
                                                if ((s16) normal_x > 0) {
                                                    *(u16 *)(ram_base + 0x010) = (u16)one;
                                                    goto L_D00F4;
                                                }
                                                if ((s16) normal_x < 0) {
                                                    *(s16 *)(ram_base + 0x010) = -1;
                                                }
L_D00F4:
                                                normal_y = *(u16 *)(ram_base + 0x012);
                                                if ((s16) normal_y > 0) {
                                                    row_step = one << *(s32 *)(ram_base + 0x124);
                                                    goto L_D0130;
                                                }
                                                if ((s16) normal_y < 0) {
                                                    row_step = 0 - (one << *(s32 *)(ram_base + 0x124));
L_D0130:
                                                    *(s16 *)(ram_base + 0x012) = (s16)row_step;
                                                }
                                                {
                                                    s32 neighbor_offset;
                                                    s32 row_offset_mask;
                                                    register s32 neighbor_column ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                                                    register s32 neighbor_row_step ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                                                    neighbor_offset = *(volatile u16 *)(ram_base + 0x010);
                                                    neighbor_column = *(volatile s32 *)(ram_base + 0x134);
                                                    neighbor_row_step = *(volatile u16 *)(ram_base + 0x012);
                                                    row_offset_mask = *(volatile s32 *)(ram_base + 0x120);
                                                    render_arg = *(volatile s32 *)(ram_base + 0x124);
                                                    neighbor_offset = (s16)neighbor_offset;
                                                    neighbor_column += neighbor_offset;
                                                    neighbor_offset = *(volatile s32 *)(ram_base + 0x11C);
                                                    neighbor_row_step = (s16)neighbor_row_step;
                                                    neighbor_column &= neighbor_offset;
                                                    neighbor_offset = *(volatile s32 *)(ram_base + 0x138);
                                                    row_offset_mask <<= render_arg;
                                                    *(volatile s32 *)(ram_base + 0x13C) = neighbor_column;
                                                    neighbor_offset += neighbor_row_step;
                                                    neighbor_offset &= row_offset_mask;
                                                    neighbor_column += neighbor_offset;
                                                    neighbor_index = neighbor_column;
                                                    *(volatile s32 *)(ram_base + 0x13C) = neighbor_index;
                                                }
                                                neighbor = (CellRec *)((neighbor_index * 6) + (s32)cells);
                                                neighbor_flags = neighbor->flags;
                                                if (!(neighbor_flags & 1)) {
                                                    if (neighbor_flags & 0x80) {
                                                        if (cells[*(s32 *)(ram_base + 0x144)].flags & 0x80) {
                                                            neighbor_face_flags = *(u8 *)(ram_base + 0x16F);
                                                            if (!(neighbor_face_flags & 2)) {
                                                                if ((*(u8 *)(ram_base + 0x16E) != one) || ((s8) neighbor_face_flags) >= 0) {
                                                                    face = (u8 *)face + 24;
                                                                    *(s32 *)(ram_base + 0x14C) = 0xFFFF;
                                                                    goto L_CFE98;
                                                                }
                                                                goto block_98;
                                                            }
                                                        }
                                                        goto block_63;
                                                    }
                                                    if (!(neighbor_flags & 0x40)) {
                                                        *(s32 *)(ram_base + 0x148) = -(s32) neighbor->offset;
                                                        goto L_D0234;
                                                    }
                                                    goto block_63;
                                                }
                                                goto block_63;
                                            }
                                        }
block_63:
                                        *(s32 *)(ram_base + 0x148) = max_height;
L_D0234:
                                        gte_ldrgb(ram_base);
                                        gte_ldv0((u8 *)normals + (*(s32 *)(ram_base + 0x14C) * 8));
                                        gte_nccs();
                                        gte_strgb(ram_base + 0x04);
                                        goto block_64;
                                    }
block_64:
                                    occlusion_height = *(s32 *)(ram_base + 0x148);
                                    if (((s16) *(u16 *)(ram_base + 0x0E4) >= occlusion_height) && ((s16) *(u16 *)(ram_base + 0x0EC) >= occlusion_height) && ((s16) *(u16 *)(ram_base + 0x0F4) >= occlusion_height) && ((s16) *(u16 *)(ram_base + 0x0FC) >= occlusion_height)) {
                                        if (((s8) *(u8 *)(ram_base + 0x16F)) >= 0) {
                                            face_skip = *(u8 *)(ram_base + 0x16E);
                                            face_skip &= 0xF;
                                            goto L_D0670;
                                        }
                                        goto block_98;
                                    }
                                    *(s32 *)(ram_base + 0x164) = ((S_800CF8E4_13 *)((((S_800CF8E4_6 *)face)->unk_06 * 8) + vertices))->unk_00;
                                    *(s32 *)(ram_base + 0x0F8) = (((u16) *(s32 *)(ram_base + 0x014) + (u16) *(s32 *)(ram_base + 0x164)) & 0xFFFF) | ((*(s32 *)(ram_base + 0x00C) + (s16) *(s32 *)(ram_base + 0x166)) << 0x10);
                                    gte_ldv0(ram_base + 0xF8);
                                    (*(s32 *)((u8 *)packet_code + 5)) = (s32) ((S_800CF8E4_6 *)face)->unk_08;
                                    gte_rtps_nn();
                                    (*(s32 *)((u8 *)packet_code + 0xD)) = (s32) ((S_800CF8E4_6 *)face)->unk_0C;
                                    (*(u16 *)((u8 *)packet_code + 0x15)) = (u16) *(s32 *)(ram_base + 0x172);
                                    (*(u16 *)((u8 *)packet_code + 0x1D)) = (u16) *(s32 *)(ram_base + 0x16C);
                                    gte_stsxy(packet + 0x20);
                                    gte_stszotz(ram_base + 0xD4);
                                    {
                                        s32 depth_sum;
                                        s32 twice_depth;
                                        s32 fourth_depth;

                                        depth_sum = *(s32 *)(ram_base + 0x0C8);
                                        fourth_depth = *(s32 *)(ram_base + 0x0D4);
                                        twice_depth = depth_sum << 1;
                                        depth_sum += twice_depth;
                                        depth_sum += fourth_depth;
                                        quad_depth = depth_sum >> 2;
                                    }
                                    *(s32 *)(ram_base + 0x0C8) = quad_depth;
                                    if ((u32) quad_depth < 0x1BEU) {
                                        ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 9;
                                        (*(s32 *)((u8 *)packet_code + -3)) = (s32) *(s32 *)(ram_base + 0x004);
                                        face_flags = *(u8 *)(ram_base + 0x16F);
                                        if (face_flags & 1) {
                                            *(u8 *)packet_code = (u8) (*(u8 *)packet_code | 2);
                                            goto L_D0540;
                                        }
                                        if ((*(u16 *)(ram_base + 0x178) != 0) && (cells[*(s32 *)(ram_base + 0x144)].flags & 0x80) && !(face_flags & 2) && ((view_height = *(s32 *)(ram_base + 0x158), (((s16) *(u16 *)(ram_base + 0x0E4) < view_height) != 0)) || ((s16) *(u16 *)(ram_base + 0x0EC) < view_height) || ((s16) *(u16 *)(ram_base + 0x0F4) < view_height) || ((s16) *(u16 *)(ram_base + 0x0FC) < view_height))) {
                                            (*(s32 *)((u8 *)packet_code + 5)) = (s32) (*(s32 *)((u8 *)packet_code + 9));
                                            (*(s32 *)((u8 *)packet_code + 9)) = (s32) (*(s32 *)((u8 *)packet_code + 0x11));
                                            (*(s32 *)((u8 *)packet_code + 0xD)) = (s32) (*(s32 *)((u8 *)packet_code + 0x19));
                                            overlay_color = *(s32 *)(ram_base + 0x110);
                                            ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 5;
                                            (*(s32 *)((u8 *)packet_code + -3)) = overlay_color;
                                            packet_code += 0x28;
                                            *(s32 *)packet = (*(s32 *)packet & tag_mask) | (*(s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC)) & address_mask);
                                            overlay_ot_entry = (s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC));
                                            {
                                                s32 overlay_addr;
                                                register s32 overlay_tag ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                                                overlay_addr = (s32) packet & address_mask;
                                                overlay_tag = *overlay_ot_entry;
                                                packet += 0x28;
                                                overlay_tag &= tag_mask;
                                                overlay_tag |= overlay_addr;
                                                *overlay_ot_entry = overlay_tag;
                                            }
                                            ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = one;
                                            {
                                                register s32 draw_mode_cmd ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                                                draw_mode_cmd = (s32) ((*(u16 *)(ram_base + 0x176) & 0x9FF) | 0xE1000000);
                                                (*(s32 *)((u8 *)packet_code + -3)) = draw_mode_cmd;
                                            }
                                        }
L_D0540:
                                        packet_code += 0x28;
                                        packet_addr = (void *) ((s32) packet & address_mask);
                                        goto L_D057C;
                                    }
                                    if ((u32) quad_depth < 0x1DEU) {
                                        ((S_800CF8E4_9_pre *)packet_code)[-1].unk_00 = 9;
                                        (*(s32 *)((u8 *)packet_code + -3)) = (s32) *(s32 *)(ram_base + 0x004);
                                        packet_addr = (void *) ((s32) packet & address_mask);
                                        ((S_800CF8E4_9 *)packet_code)->unk_00 = (u8) (((S_800CF8E4_9 *)packet_code)->unk_00 | 2);
                                        packet_code += 0x28;
L_D057C:
                                        *(s32 *)packet = (*(s32 *)packet & tag_mask) | (*(s32 *)((*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC)) & address_mask);
                                        ot_entry = (*(s32 *)(ram_base + 0x0C8) * 4) + *(s32 *)(ram_base + 0x0BC);
                                        *ot_entry = (*ot_entry & tag_mask) | (s32) packet_addr;
                                        packet += 0x28;
                                        face_skip = *(u8 *)(ram_base + 0x16E);
                                        if ((face_skip & 0xF) == one) {
                                            if (((s8) *(u8 *)(ram_base + 0x16F)) < 0) {
                                                goto block_98;
                                            }
                                            face = (u8 *)face + ((((u32)face_skip >> 4) * 24) + 24);
                                            goto L_CFE98;
                                        }
                                        goto L_D063C;
                                    }
                                    goto block_98;
                                }
                                goto block_98;
                            }
                            if (((S_800CF8E4_10 *)(((*(u16 *)(ram_base + 0x170) * 8) + normals)))->unk_04 >= 0) {
                                goto L_D0644;
                            }
                            {
                                s32 end_marker;
                                register s32 face_marker ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

                                end_marker = 0x8001;
                                face_marker = *(u16 *)(ram_base + 0x16E) & 0x80FF;
                                if (face_marker == end_marker) {
                                    goto block_98;
                                }
                            }
L_D063C:
                            face = (u8 *)face + 24;
                            goto L_CFE98;
L_D0644:
                            face_skip = *(u8 *)(ram_base + 0x16E);
                            if (!(face_skip & 0xF0)) {
                                if (((s8) *(u8 *)(ram_base + 0x16F)) < 0) {
                                    goto block_98;
                                }
                            }
                            face_skip &= 0xF;
L_D0670:
                            face = (u8 *)face + (face_skip * 24);
                            goto L_CFE98;
block_98:
                            if ((u32) *(s32 *)(ram_base + 0x17C) >= (u32) packet) {
                                goto block_99;
                            }
                            goto block_106;
                        }
block_99:
                        next_column = *(s32 *)(ram_base + 0x134) + 1;
                        *(s32 *)(ram_base + 0x134) = next_column;
                        *(s32 *)(ram_base + 0x134) = next_column & *(s32 *)(ram_base + 0x11C);
                        next_x = *(s32 *)(ram_base + 0x014) + 0x40;
                        *(s32 *)(ram_base + 0x014) = next_x;
                        if (*(s32 *)(ram_base + 0x018) < next_x) {
                            goto block_100;
                        }
                        goto loop_36;
                    }
                    goto block_100;
                }
block_100:
                render_arg = 3;
                minus_one = -1;
                edge_end = (s32 *)(ram_base + 0x78);
                *(s32 *)(ram_base + 0x00C) += 0x40;
                do {
                    ASM_KEEP(edge_end);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    if (((S_800CF8E4_11 *)edge_end)->unk_38 > 0) {
                        edge_remaining = ((S_800CF8E4_11 *)edge_end)->unk_28 - 0x40;
                        ((S_800CF8E4_11 *)edge_end)->unk_28 = edge_remaining;
                        if (edge_remaining < -0x7F) {
                            ((S_800CF8E4_11 *)edge_end)->unk_38 = minus_one;
                            *(u16 *)(ram_base + 0x174) = (u16) (*(u16 *)(ram_base + 0x174) - 1);
                        }
                    }
                    render_arg -= 1;
                    edge_end -= 0x28;
                } while (render_arg >= 0);
                if (*(u16 *)(ram_base + 0x174) == 0) {
                    goto block_106;
                }
                goto loop_9;
            }
            goto loop_15;
        }
block_106:
        ((S_800CF8E4_14 *)(((S_800CF8E4_0 *)scene)->unk_00))->unk_8D0 = packet;
    }
}
