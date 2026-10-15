#include "modules/dungeon_ovl_1930844.h"

void func_8002429C(void *effect_data, void *origin, s16 step_index, s16 scale_factor)
{
    s32 scale;
    register s32 step;
    u32 addr_mask;
    s32 angle;
    u8 *scratch;
    GameWork *render_global;
    u8 *line_packet;
    void *start_vertex;
    void *start_screen;
    void *end_vertex;
    void *end_screen;
    u8 * draw_mode_packet;
    s32 radial_x;
    s32 radial_y;
    s32 ray_index = 0;
    s32 prev_step;
    render_global = &gameWork;
    scale = (s16) scale_factor;
    step = (s16) step_index;
    prev_step = step - 1;
    addr_mask = 0x00FFFFFF;
    angle = 0;
    scratch = (u8 *) 0x1F800000;
    *((void **) (((u8 *) scratch) + 0x18)) = (*((u8 **) ((u8 *)(&gameWork)))) + 0xB0;
    do {
        void **render_ptr = (void **) render_global;
        void *render_ctx = *render_ptr;
        s32 start_step_offset;
        s32 end_step_offset;
        s32 z_delta;
        s32 z_step;
        s32 avg_depth;
        void *origin_ptr;
        u16 origin_coord;
        line_packet = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
        *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = line_packet + 0x14;
        *((u8 *) (((u8 *) line_packet) + 3)) = 4;
        *((u8 *) (((u8 *) line_packet) + 7)) = 0x52;
        *((u8 *) (((u8 *) line_packet) + 4)) = *((u8 *) (((u8 *) effect_data) + 0x40));
        *((u8 *) (((u8 *) line_packet) + 5)) = *((u8 *) (((u8 *) effect_data) + 0x41));
        *((u8 *) (((u8 *) line_packet) + 6)) = *((u8 *) (((u8 *) effect_data) + 0x42));
        *((u8 *) (((u8 *) line_packet) + 0xC)) = *((u8 *) (((u8 *) effect_data) + 0x40));
        *((u8 *) (((u8 *) line_packet) + 0xD)) = *((u8 *) (((u8 *) effect_data) + 0x41));
        *((u8 *) (((u8 *) line_packet) + 0xE)) = *((u8 *) (((u8 *) effect_data) + 0x42));
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 2));
        *((u16 *) (((u8 *) scratch) + 0x6C)) = origin_coord;
        *((u16 *) (((u8 *) scratch) + 0x64)) = origin_coord;
        radial_x = ((func_800644B8(angle + (*((s16 *) (((u8 *) effect_data) + 0xA))))
            >> 4) * (*((s16 *) (((u8 *) effect_data) + 0xE)))) << 8;
        start_step_offset = radial_x / scale;
        *((s32 *) (((u8 *) scratch) + 0x108)) = radial_x;
        *((u16 *) (((u8 *) scratch) + 0x64)) += (start_step_offset * prev_step) >> 16;
        end_step_offset = (*((s32 *) (((u8 *) scratch) + 0x108))) / scale;
        *((u16 *) (((u8 *) scratch) + 0x6C)) += (end_step_offset * step) >> 16;
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 6));
        *((u16 *) (((u8 *) scratch) + 0x6E)) = origin_coord;
        *((u16 *) (((u8 *) scratch) + 0x66)) = origin_coord;
        start_vertex = scratch + 0x64;
        start_screen = scratch + 0xD8;
        end_vertex = scratch + 0x6C;
        end_screen = scratch + 0xDC;
        radial_y = ((func_80064584(angle + (*((s16 *) (((u8 *) effect_data) + 0xA))))
            >> 4) * (*((s16 *) (((u8 *) effect_data) + 0xE)))) << 8;
        start_step_offset = radial_y / scale;
        *((s32 *) (((u8 *) scratch) + 0x10C)) = radial_y;
        *((u16 *) (((u8 *) scratch) + 0x66)) += (start_step_offset * prev_step) >> 16;
        end_step_offset = (*((s32 *) (((u8 *) scratch) + 0x10C))) / scale;
        render_ptr = (void **)(scratch + 0x84);
        *((u16 *) (((u8 *) scratch) + 0x6E)) += (end_step_offset * step) >> 16;
        origin_ptr = origin;
        origin_coord = *((u16 *) (((u8 *) origin_ptr) + 0xA));
        *((u16 *) (((u8 *) scratch) + 0x70)) = origin_coord;
        *((u16 *) (((u8 *) scratch) + 0x68)) = origin_coord;
        z_delta = (((s32) (*((s16 *) (((u8 *) effect_data) + 0x14)))) << 16) - (*((s32 *) (((u8 *) origin_ptr) + 8)));
        *((s32 *) (((u8 *) scratch) + 0x110)) = z_delta;
        z_step = z_delta >> scale;
        *((u16 *) (((u8 *) scratch) + 0x68)) += (z_step << prev_step) >> 16;
        *((u16 *) (((u8 *) scratch) + 0x70)) += (((*((s32 *) (scratch + 0x110))) >> scale) << step) >> 16;
        origin_ptr = scratch + 0x88;
        *((s32 *) (((u8 *) scratch) + 0xF4)) = func_80065420(start_vertex, start_screen, render_ptr, origin_ptr);
        *((s32 *) (((u8 *) scratch) + 0xF8)) = func_80065420(end_vertex, end_screen, render_ptr,
            origin_ptr);
        *((u16 *) (((u8 *) line_packet) + 8)) = *((u16 *) (((u8 *) scratch) + 0xD8));
        *((u16 *) (((u8 *) line_packet) + 0xA)) = *((u16 *) (((u8 *) scratch) + 0xDA));
        *((u16 *) (((u8 *) line_packet) + 0x10)) = *((u16 *) (((u8 *) scratch) + 0xDC));
        *((u16 *) (((u8 *) line_packet) + 0x12)) = *((u16 *) (((u8 *) scratch) + 0xDE));
        avg_depth = ((*((s32 *) (((u8 *) scratch) + 0xF4))) + (*((s32 *) (((u8 *) scratch) + 0xF8)))) / 2;
        *((s32 *) (((u8 *) scratch) + 0xB4)) = avg_depth;
        if (((u32) avg_depth) < 0x1E0U) {
            OT_SETADDR(line_packet, OT_GETADDR((*((u32 **) (((u8 *) scratch) + 0x18))) + avg_depth, addr_mask),
                0xFF000000, addr_mask);
            *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4)))))
                + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18)))
                + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) line_packet) & addr_mask);
            render_ptr = (void **) render_global;
            render_ctx = *render_ptr;
            draw_mode_packet = *((u8 **) (((u8 *) render_ctx) + 0x8D0));
            *((u8 **) (((u8 *) render_ctx) + 0x8D0)) = draw_mode_packet + 0xC;
            func_80067F20(draw_mode_packet, 0, 0, func_80066460(0, *((s16 *) (((u8 *) effect_data) + 0x12)), 0,
                0) & 0xFFFF, 0);
            OT_SETADDR(draw_mode_packet, OT_GETADDR((*((u32 **) (((u8 *) scratch) + 0x18)))
                + (*((s32 *) (((u8 *) scratch) + 0xB4))), addr_mask), 0xFF000000, addr_mask);
            *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18))) + (*((s32 *) (((u8 *) scratch) + 0xB4)))))
                + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) scratch) + 0x18)))
                + (*((s32 *) (((u8 *) scratch) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) draw_mode_packet) & addr_mask);
        }
        angle += 0x333;
        ray_index++;
    }
    while (ray_index < 5);
}
