#include "common.h"

typedef struct S_8182121C_0 {
    u32 unk_00;
    s32 unk_04;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_8182121C_0;   /* packet1 in func_8182121C */

typedef struct S_8182121C_1 {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x8];
    s16 unk_54;
} S_8182121C_1;   /* item in func_8182121C */

typedef struct S_8182121C_2 {
    u8 pad_00[0xB0];
    u32 unk_B0;
} S_8182121C_2;   /* entry in func_8182121C */

typedef struct S_8182121C_3 {
    u32 unk_00;
} S_8182121C_3;   /* packet0 in func_8182121C */

typedef struct S_8182121C_4_pre {
    s32 unk_00;
    u8 pad_04[0x4];
} S_8182121C_4_pre;   /* the 0x8 bytes before outer in func_8182121C, addressed as outer[-1] */


extern u8 D_80083160[];

extern s32 func_80065420();
extern s32 func_80066460();
extern void func_80066640();
extern void func_80066690();
extern void func_80067F20();
extern s32 func_80069EF8();


/* Draw four jittered triangles per linked item into the ordering table. */
s32 func_8182121C(void *first_item)
{
    u16 screen_coords[3];
    void *list_item;
    void *item_data;
    register s32 next_node ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    u8 **render_context;
    u8 *draw_mode;
    u8 *triangle;
    u32 depth_index;
    s32 point_index;
    register u32 addr_mask ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+byte_offset) depends on it */
    u32 length_mask;
    s32 blend_mode;
    s32 byte_offset;
    u32 *ot_entry_base;
    u32 ot_tag;

    list_item = first_item;
    render_context = (u8 **)D_80083160;
    addr_mask = 0x00FFFFFF;
    length_mask = 0xFF000000;

    do {
        item_data = list_item;
        point_index = 3;
        do {
            draw_mode = render_context[0] + 0x8D0;
            draw_mode = *(u8 **)draw_mode;
            *(u8 **)(render_context[0] + 0x8D0) = draw_mode + 0xC;

            triangle = *(u8 **)(render_context[0] + 0x8D0);
            *(u8 **)(render_context[0] + 0x8D0) = triangle + 0x14;

            ((S_8182121C_0 *)triangle)->unk_04 = ((S_8182121C_1 *)item_data)->unk_48;
            func_80066690(triangle);
            func_80066640(triangle, 1);

            blend_mode = 3;
            if (((S_8182121C_1 *)item_data)->unk_54 > 0) {
                blend_mode = 1;
            }
            func_80067F20(draw_mode, 0, 0,
                func_80066460(0, blend_mode, 0, 0) & 0xFFFF, 0);

            byte_offset = (point_index * 8) + 0x28;
            depth_index = func_80065420((u8 *)item_data + byte_offset,
                screen_coords, &screen_coords[2], &screen_coords[2]) - 8;

            ((S_8182121C_0 *)triangle)->unk_08 = screen_coords[0] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)triangle)->unk_0A = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)triangle)->unk_0C = screen_coords[0] - (func_80069EF8() & 1) - 1;
            ((S_8182121C_0 *)triangle)->unk_0E = screen_coords[1] + (func_80069EF8() & 1) + 1;
            ((S_8182121C_0 *)triangle)->unk_10 = screen_coords[0] + (func_80069EF8() & 4) - 2;
            ((S_8182121C_0 *)triangle)->unk_12 = screen_coords[1] - (func_80069EF8() & 1) - 1;

            if (depth_index < 0x1E0U) {
                byte_offset = depth_index * 4;
                (*(u32 *)((u8 *)triangle + 0)) =
                    (((S_8182121C_0 *)triangle)->unk_00 & length_mask) |
                    (((u32 *)(render_context[0] + 0xB0))[depth_index] & addr_mask);
                ot_entry_base = (u32 *)(byte_offset + (s32) render_context[0]);
                ot_tag = ((S_8182121C_2 *)ot_entry_base)->unk_B0;
                (*(u32 *)((u8 *)ot_entry_base + 0xB0)) = (ot_tag & length_mask) |
                    ((u32)triangle & addr_mask);

                (*(u32 *)((u8 *)draw_mode + 0)) =
                    (((S_8182121C_3 *)draw_mode)->unk_00 & length_mask) |
                    (((u32 *)(render_context[0] + 0xB0))[depth_index] & addr_mask);
                ((u32 *)(render_context[0] + 0xB0))[depth_index] =
                    (((u32 *)(render_context[0] + 0xB0))[depth_index] & length_mask) |
                    ((u32)draw_mode & addr_mask);
            }
            point_index--;
        } while (point_index >= 0);

        next_node = ((S_8182121C_4_pre *)list_item)[-1].unk_00;
        list_item = (void *)(next_node + 0x20);
    } while (next_node != 0);

    ASM_KEEP(next_node);   /* MATCH pin: retail register colouring depends on it */
    return 0;
}
