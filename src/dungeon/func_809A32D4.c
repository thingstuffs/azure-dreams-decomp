#include "modules/dungeon_ovl_9c32d4.h"

void update_actor_render_effect_and_position(u8 *actor_data, u8 *output_data, u8 *effect_data)
{
    ovl_9c32d4_809A32D4_LocalArgs draw_region;
    ovl_9c32d4_809A32D4_Actor *actor;
    ovl_9c32d4_809A32D4_Output *output;
    u8 *initial_page;
    u8 *rect_page;
    u8 *region_page;
    u8 *base_page;
    u8 *packet_list;
    void *page_packet;
    void *rect_packet;
    void *region_packet;
    u8 alternate_page;
    u8 adjust_y;
    s16 steps_left;
    s16 next_steps;
    s32 draw_y;
    s32 texture_u;
    s32 packed_size;
    s32 state;
    u8 decay_level;
    u8 rise_level;

    actor = (ovl_9c32d4_809A32D4_Actor *)actor_data;
    output = (ovl_9c32d4_809A32D4_Output *)output_data;
    initial_page = DUNGEON_INITIAL;
    base_page = D_801C9E40;
    state = actor->state;
    alternate_page = initial_page != base_page;
    packet_list = initial_page + 0xB0;

    if (state == 0) {
        page_packet = ((ovl_9c32d4_809A32D4_S_80174AD4_0 *)initial_page)->unk_8D0;
        ((ovl_9c32d4_809A32D4_S_80174AD4_0 *)initial_page)->unk_8D0 = (u8 *)page_packet + 0xC;
        func_80067E2C(page_packet, DUNGEON_FROM_PAGE);
        func_8006658C(packet_list, page_packet);

        draw_y = 0x110;
        draw_region.x = 0x340;
        draw_region.y = 0x100;
        draw_region.w = 0x20;
        draw_region.h = 0x20;
        texture_u = 0x350;
        draw_region.u = texture_u;
        adjust_y = alternate_page;
        if (adjust_y != 0) {
            draw_y = 0x30;
        }
        draw_region.v = draw_y;

        emit_concentric_ellipse_quads(0x10, 0x10, 0, 0, texture_u, draw_region.v,
                      actor, (u8 *)actor + 4, packet_list, 0, 0x20);

        rect_page = DUNGEON_FROM_PAGE;
        rect_packet = ((ovl_9c32d4_809A32D4_S_80174AD4_1 *)rect_page)->unk_8D0;
        ((ovl_9c32d4_809A32D4_S_80174AD4_1 *)rect_page)->unk_8D0 = (u8 *)rect_packet + 0x10;
        ((ovl_9c32d4_809A32D4_S_80174AD4_2 *)rect_packet)->unk_04 = 0x60000000;
        ((ovl_9c32d4_809A32D4_S_80174AD4_2 *)rect_packet)->unk_03 = 3;
        ((ovl_9c32d4_809A32D4_S_80174AD4_2 *)rect_packet)->unk_08 = draw_region.x;
        draw_y = draw_region.y;
        if (adjust_y != 0) {
            draw_y -= 0xE0;
        }
        packed_size = *(s32 *)&draw_region.w;
        ((ovl_9c32d4_809A32D4_S_80174AD4_2 *)rect_packet)->unk_0A = draw_y;
        ((ovl_9c32d4_809A32D4_S_80174AD4_2 *)rect_packet)->unk_0C = packed_size;
        func_8006658C(packet_list, rect_packet);

        region_page = DUNGEON_FROM_PAGE;
        region_packet = ((ovl_9c32d4_809A32D4_S_80174AD4_3 *)region_page)->unk_8D0;
        ((ovl_9c32d4_809A32D4_S_80174AD4_3 *)region_page)->unk_8D0 = (u8 *)region_packet + 0xC;
        func_80067E2C(region_packet, (void *)&draw_region);
        func_8006658C(packet_list, region_packet);
        actor->state++;
    } else if (state == 1) {
        func_8004491C((u8 *)actor - 0x20, process_linked_mesh_states_mode_0);
        actor->state++;
    } else if (state == 3) {
        decay_level = ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C;
        if (decay_level != 0) {
            decay_level -= 8;
            ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C = decay_level;
            if (decay_level == 0) {
                (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
                object_flag_block.flags |= 0x8000;
            }
        }
    } else {
        rise_level = ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C;
        if (rise_level < 0xC0) {
            ((ovl_9c32d4_809A32D4_S_80174AD4_4 *)effect_data)->unk_0C = rise_level + 0x20;
        }
        if (actor->field16 != *actor->field10) {
            actor->state++;
        }
    }
    steps_left = 4;
    if (actor->state != 3) {
        output->field02 = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_02;
        output->field06 = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_06;
        output->field0A = ((ovl_9c32d4_809A32D4_S_80174AD4_5 *)(actor->field1C))->unk_0A - 0xC;
        do {
            spawn_randomized_directional_motion_object((u8 *)actor - 0x20, (((ovl_9c32d4_809A32D4_S_80174AD4_7 *)(((ovl_9c32d4_809A32D4_S_80174AD4_6 *)actor)->unk_0C))->unk_00 >> 9) & 7,
                0xFF);
            next_steps = steps_left - 1;
            steps_left = next_steps;
        } while ((next_steps << 16) > 0);
    }
}
