/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800970FC_0 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_800970FC_0;   /* entry in func_800970FC */

typedef struct S_800970FC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800970FC_1;   /* coord in func_800970FC */

typedef struct S_800970FC_2 {
    u16 unk_00;
} S_800970FC_2;   /* &D_800D0504 in func_800970FC */

typedef struct S_800970FC_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_3;   /* CUR_PAGE in func_800970FC */

typedef struct S_800970FC_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    u8 pad_0E[0x6];
    s8 unk_14;
    s8 unk_15;
    s16 unk_16;
    u8 pad_18[0x4];
    s8 unk_1C;
    s8 unk_1D;
    u8 pad_1E[0x6];
    s8 unk_24;
    s8 unk_25;
} S_800970FC_4;   /* temp_s0_2 in func_800970FC */

typedef struct S_800970FC_5 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_800970FC_5;   /* D_800D04D0 in func_800970FC */

typedef struct S_800970FC_6 {
    u16 unk_00;
    union { u16 u; s16 s; } unk_02;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_04;   /* accessed as both */
    union { u8 u8; u16 u16; } unk_06;   /* accessed as both */
} S_800970FC_6;   /* xy in func_800970FC */

typedef struct S_800970FC_7 {
    u16 unk_00;
} S_800970FC_7;   /* D_800D04D8 in func_800970FC */

typedef struct S_800970FC_8 {
    u8 pad_00[0x2];
    s16 unk_02;
    u16 unk_04;
    u16 unk_06;
} S_800970FC_8;   /* rect in func_800970FC */

typedef struct S_800970FC_9 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_9;   /* CUR_CTX in func_800970FC */

typedef struct S_800970FC_10 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_10;   /* temp_s0_3 in func_800970FC */

typedef struct S_800970FC_11 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    u8 pad_07[0x1];
    u16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    u16 unk_10;
    s16 unk_12;
    s16 unk_14;
} S_800970FC_11;   /* temp_s0_4 in func_800970FC */

typedef struct S_800970FC_12 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_800970FC_12;   /* late_entry in func_800970FC */

typedef struct S_800970FC_13 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800970FC_13;   /* late_ctx in func_800970FC */

typedef struct S_800970FC_14 {
    u8 pad_00[0x4];
    u8 unk_04;
    u8 unk_05;
    u8 unk_06;
} S_800970FC_14;   /* temp_s0_8 in func_800970FC */


extern void func_80044D24(void *, void *, s32);
extern void func_800453E0(void *, void *, void *, s16);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_8006658C(void *, void *);
extern void func_80066640(void *, s32);
extern void func_800666E0(void *);
extern void func_800666F4(void *);
extern void func_80067E2C(void *, void *);
extern void func_80067EF4(void *, s32, s32);
extern s32 func_8008C180(s16, s16);
extern s32 func_800C1D44(s32);
extern u8 D_80082E80[];
extern u8 D_800834B8[];
extern u8 D_80083780[];
extern s32 D_800D0460[3];
extern u8 D_800D04D0[];
extern u8 D_800D04D8[];
extern u8 D_800D04E0[];
extern u8 D_800D0504[];
extern s16 D_800D45AA[];
extern u8 D_801C9E40[];

extern void *D_80083160[3];

#define CUR_CTX (*page_state)
#define CUR_PAGE (D_80083160[0])

/* Draws the entry and its height-dependent textured and solid overlays. */
s32 func_800970FC(void) {
    s32 page_offset;
    s32 texture_y;
    s32 rounded_texture_y;
    s16 draw_y;
    s16 draw_x;
    s32 rect_y;
    s32 texture_top;
    s32 alternate_page;
    s16 page_index;
    s32 overlay_height;
    s32 height_index;
    s32 height_delta;
    s32 coord_z;
    s32 coord_x;
    s32 coord_y;
    s32 color;
    s32 page_mask;
    s32 texture_depth;
    u16 saved_draw_param;
    u32 saved_flags;
    u16 rotation;
    u16 quad_x;
    void *primitive;
    u8 *entry;
    u8 *coord;
    u8 *texture_rect;
    u8 *draw_entry;
    u8 *draw_ctx;
    void **page_state;
    u32 *scratch_control;
    u16 *scratch_x;
    u16 *scratch_y;
    u16 rect_width;
    u32 rect_height;
    u32 fill_height;

    page_state = &D_80083160[0];
    entry = D_80082E80;
    alternate_page = CUR_PAGE != (void *)D_801C9E40;
    rotation = ((S_800970FC_0 *)entry)->unk_06;
    page_index = (u16) alternate_page;
    if (!(((S_800970FC_0 *)entry)->unk_14 & 0x80)) {
        coord = D_80083780;
#define D_80083780 (*coord)
        D_800D0460[0] = 0;
        coord_x = ((S_800970FC_1 *)coord)->unk_02;
        coord_y = ((S_800970FC_1 *)coord)->unk_06;
        height_index = func_800C1D44(func_8008C180(coord_x, coord_y) & 0xFFFF);
        if (height_index != 0) {
            coord_z = ((S_800970FC_1 *)coord)->unk_0A;
            height_delta = (s32) (coord_z - D_800D45AA[height_index]) / 2;
            overlay_height = height_delta;
            overlay_height = overlay_height + 6;
            if ((u32) ((height_delta + 5) & 0xFFFF) < 0x3FU) {
                D_800D0460[0] = 1;
                scratch_control = (u32 *)0x1F80013C;
                *scratch_control = 0;
                func_800453E0(NULL, coord, D_800D04E0, (s16) (rotation + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
                scratch_control = (void *)0;
                scratch_control = (u32 *)0x1F80013C;
                *scratch_control = 0;
                func_800453E0(D_800834B8, coord, entry, (s16) (rotation + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
                primitive = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (primitive + 0xC);
                func_80067E2C(primitive, CUR_PAGE);
                func_8006658C(CUR_PAGE + 0x830, primitive);
                primitive = ((S_800970FC_3 *)CUR_PAGE)->unk_8D0;
                ((S_800970FC_3 *)CUR_PAGE)->unk_8D0 = (void *) (primitive + 0x28);
                color = 0x808080;
                ((S_800970FC_4 *)primitive)->unk_04 = color;
                func_800666F4(primitive);
                texture_depth = 2;
                color = texture_depth;
                texture_rect = D_800D04D0;
                page_mask = ~0xFF;
                ((S_800970FC_4 *)primitive)->unk_16 = func_80066460(texture_depth, color, (s16) (((S_800970FC_5 *)D_800D04D0)->unk_00.u & page_mask), (s16) (((S_800970FC_6 *)texture_rect)->unk_02.u & page_mask));
                func_80066640(primitive, 1);
                ((S_800970FC_4 *)primitive)->unk_0C = (s8) (((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_0D = (s8) (((S_800970FC_6 *)texture_rect)->unk_02.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_14 = (s8) ((((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100) + ((S_800970FC_6 *)texture_rect)->unk_04.u8);
                ((S_800970FC_4 *)primitive)->unk_15 = (s8) (((S_800970FC_6 *)texture_rect)->unk_02.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_1C = (s8) (((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100);
                ((S_800970FC_4 *)primitive)->unk_1D = (s8) ((((S_800970FC_6 *)texture_rect)->unk_02.s % 0x100) + ((S_800970FC_6 *)texture_rect)->unk_06.u8);
                ((S_800970FC_4 *)primitive)->unk_24 = (s8) ((((S_800970FC_5 *)D_800D04D0)->unk_00.s % 0x100) + ((S_800970FC_6 *)texture_rect)->unk_04.u8);
                texture_y = ((S_800970FC_6 *)texture_rect)->unk_02.s;
                if (texture_y < 0) {
                    rounded_texture_y = texture_y + 0xFF;
                    page_offset = alternate_page;
                } else {
                    rounded_texture_y = texture_y;
                    page_offset = page_index;
                }
                ((S_800970FC_4 *)primitive)->unk_25 =
                    (s8)(texture_y - ((rounded_texture_y >> 8) * 0x100) +
                         ((S_800970FC_6 *)texture_rect)->unk_06.u8);
                {
                    u8 *rect;
                    u32 edge_height;
                    rect = D_800D04D8;
                    quad_x = ((S_800970FC_7 *)D_800D04D8)->unk_00;
                    rect_y = ((S_800970FC_8 *)rect)->unk_02;
                    page_offset = page_index;
                    if (page_offset != 0) {
                        rect_y -= 0xE0;
                    }
                    (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                    (*(s16 *)((u8 *)primitive + 0xA)) = rect_y;
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x10)) = (s16) (quad_x + rect_width);
                    (*(s16 *)((u8 *)primitive + 0x12)) = rect_y;
                    (*(u16 *)((u8 *)primitive + 0x18)) = quad_x;
                    rect_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x1A)) = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x20)) = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x22)) = (s16) (rect_y + rect_height);
                    func_8006658C(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                    ((S_800970FC_10 *)primitive)->unk_04 = 0x40;
                    ((S_800970FC_10 *)primitive)->unk_05 = 0x40;
                    ((S_800970FC_10 *)primitive)->unk_06 = 0xC0;
                    func_800666E0(primitive);
                    func_80066640(primitive, 0);
                    (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                    fill_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0xA)) = (s16) ((rect_y + fill_height) - overlay_height);
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    (*(s16 *)((u8 *)primitive + 0xC)) = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    edge_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(u16 *)((u8 *)primitive + 0x10)) = quad_x;
                    (*(s16 *)((u8 *)primitive + 0xE)) = (s16) ((rect_y + edge_height) - overlay_height);
                    edge_height = 0;
                    fill_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x12)) = (s16) (rect_y + fill_height);
                    rect_width = 0;
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    (*(s16 *)((u8 *)primitive + 0x14)) = (s16) (quad_x + rect_width);
                    fill_height = 0;
                    fill_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x16)) = (s16) (rect_y + fill_height);
                    func_8006658C(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                    ((S_800970FC_11 *)primitive)->unk_06 = 0;
                    ((S_800970FC_11 *)primitive)->unk_05 = 0;
                    ((S_800970FC_11 *)primitive)->unk_04 = 0;
                    func_800666E0(primitive);
                    func_80066640(primitive, 0);
                    ((S_800970FC_11 *)primitive)->unk_08 = quad_x;
                    ((S_800970FC_11 *)primitive)->unk_0A = rect_y;
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    ((S_800970FC_11 *)primitive)->unk_0C = (s16) (quad_x + rect_width);
                    ((S_800970FC_11 *)primitive)->unk_0E = rect_y;
                    ((S_800970FC_11 *)primitive)->unk_10 = quad_x;
                    rect_height = ((S_800970FC_8 *)rect)->unk_06;
                    ((S_800970FC_11 *)primitive)->unk_12 = (s16) (rect_y + rect_height);
                    rect_width = 0;
                    rect_width = ((S_800970FC_8 *)rect)->unk_04;
                    ((S_800970FC_11 *)primitive)->unk_14 = (s16) (quad_x + rect_width);
                    rect_height = 0;
                    rect_height = ((S_800970FC_8 *)rect)->unk_06;
                    (*(s16 *)((u8 *)primitive + 0x16)) = (s16) (rect_y + rect_height);
                    func_8006658C(CUR_CTX + 0x830, primitive);
                    primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                    ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                    func_80067E2C(primitive, rect);
                    func_8006658C(CUR_CTX + 0x830, primitive);
                }
                draw_entry = D_80082E80;
                quad_x = ((S_800970FC_6 *)texture_rect)->unk_00;
                texture_top = ((S_800970FC_6 *)texture_rect)->unk_02.s;
                saved_flags = ((S_800970FC_12 *)draw_entry)->unk_14;
                saved_draw_param = ((S_800970FC_12 *)draw_entry)->unk_10;
                {
                    if (page_offset != 0) {
                        texture_top -= 0xE0;
                    }
                }
                draw_x = quad_x + 0x20;
                draw_y = texture_top + 0x39;
                scratch_x = (u16 *)0x1F800000;
                scratch_y = (u16 *)0x1F800002;
                *scratch_x = (u16) draw_x;
                *scratch_y = (u16) draw_y;
                ((S_800970FC_12 *)draw_entry)->unk_10 = 0x40U;
                ((S_800970FC_12 *)draw_entry)->unk_14 = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) | 0xC);
                func_80044D24(0, draw_entry, 0x1F0);
                scratch_x = (void *)0;
                scratch_y = (void *)0;
                scratch_x = (u16 *)0x1F800000;
                scratch_y = (u16 *)0x1F800002;
                *scratch_x = (u16) draw_x;
                *scratch_y = (u16) draw_y;
                ((S_800970FC_12 *)draw_entry)->unk_10 = 0x20U;
                ((S_800970FC_12 *)draw_entry)->unk_14 = (u16) ((*(u16 *)((u8 *)draw_entry + 0x14)) & 0xFFF3);
                func_80044D24(0, draw_entry, 0x1F0);
                draw_ctx = CUR_CTX;
                ((S_800970FC_12 *)draw_entry)->unk_14 = saved_flags;
                ((S_800970FC_12 *)draw_entry)->unk_10 = saved_draw_param;
                primitive = ((S_800970FC_13 *)draw_ctx)->unk_8D0;
                ((S_800970FC_13 *)draw_ctx)->unk_8D0 = (void *) (primitive + 0xC);
                func_80067EF4(primitive, 0, 0);
                func_8006658C(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0x18);
                ((S_800970FC_14 *)primitive)->unk_06 = 0xFF;
                ((S_800970FC_14 *)primitive)->unk_05 = 0xFF;
                ((S_800970FC_14 *)primitive)->unk_04 = 0xFF;
                func_800666E0(primitive);
                func_80066640(primitive, 0);
                (*(u16 *)((u8 *)primitive + 8)) = quad_x;
                (*(s16 *)((u8 *)primitive + 0xA)) = texture_top;
                (*(s16 *)((u8 *)primitive + 0xC)) = (s16) (quad_x + ((S_800970FC_6 *)texture_rect)->unk_04.u16);
                (*(s16 *)((u8 *)primitive + 0xE)) = texture_top;
                (*(u16 *)((u8 *)primitive + 0x10)) = quad_x;
                (*(s16 *)((u8 *)primitive + 0x12)) = (s16) (texture_top + ((S_800970FC_6 *)texture_rect)->unk_06.u16);
                (*(s16 *)((u8 *)primitive + 0x14)) = (s16) (quad_x + ((S_800970FC_6 *)texture_rect)->unk_04.u16);
                (*(s16 *)((u8 *)primitive + 0x16)) = (s16) (texture_top + ((S_800970FC_6 *)texture_rect)->unk_06.u16);
                func_8006658C(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                func_80067EF4(primitive, 0, 1);
                func_8006658C(CUR_CTX + 0x830, primitive);
                primitive = ((S_800970FC_9 *)CUR_CTX)->unk_8D0;
                ((S_800970FC_9 *)CUR_CTX)->unk_8D0 = (void *) (primitive + 0xC);
                func_80067E2C(primitive, texture_rect);
                func_8006658C(CUR_CTX + 0x830, primitive);
                return 0;
            }
        }
        scratch_control = (void *)0;
        scratch_control = (u32 *)0x1F80013C;
        *scratch_control = 0;
        func_800453E0(D_800834B8, coord, entry, (s16) (rotation + ((S_800970FC_2 *)(&D_800D0504))->unk_00));
        return 0;
    }
    return 0;
}
