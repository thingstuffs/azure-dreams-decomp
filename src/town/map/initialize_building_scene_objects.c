#include "common.h"

typedef struct {
    u16 field0;
    u16 field2;
    u8 field4;
    u8 field5;
} Event6;

extern u8 town_building_scene_index;
extern Event6 D_800D1910[];
extern u8 town_map_variants[];
extern u8 town_map_selection_state[12];
extern u8 D_80126494[12];
extern u8 D_8012669C[12];
extern u8 D_80126884[12];
extern u8 D_80126A6C[12];
extern u8 D_80126C54[12];
extern u8 D_80126E3C[12];
extern u8 D_80127024[12];
extern u8 D_80127FA8[12];

void initialize_shared_script_data(void);
void scale_coordinates_and_append_pointers(s32, s32, s32, s32, void *);
void create_entry_builder_controller(void);
void set_texture_quad_32_uv(s32, s32, s32, s32);
void blit_indexed_origin_u16_block(s32, s32, s32, s32);
void blit_origin_u16_block(s32, s32, void *, s32);

/* Draws the active town entry and its state-dependent overlays. */
void initialize_building_scene_objects(s32 draw_param) {
    Event6 *event;
    Event6 *event_table;
    u8 *draw_state;
    u8 *status_page;
    s32 entry_kind;
    s32 draw_x;
    s16 draw_kind;
    u32 overlay_index;

    initialize_shared_script_data();
    draw_state = town_map_selection_state;
    if (draw_state[6] != 0) {
        draw_x = draw_state[0];
        entry_kind = town_map_variants[draw_state[6] * 32];
        draw_kind = entry_kind;
        blit_indexed_origin_u16_block(draw_x, draw_state[1], draw_kind, draw_param);
        if (draw_kind == 0x26) {
            overlay_index = town_building_scene_index - 6;
            switch (overlay_index) {
            case 0:
                blit_origin_u16_block(0x2E, 0x24, D_8012669C, draw_param);
                break;
            case 2:
                blit_origin_u16_block(0x2E, 0x24, D_80126884, draw_param);
                break;
            case 3:
                blit_origin_u16_block(0x2E, 0x24, D_80126A6C, draw_param);
                break;
            case 5:
                blit_origin_u16_block(0x2E, 0x24, D_80126C54, draw_param);
                break;
            case 6:
                blit_origin_u16_block(0x2E, 0x24, D_80126E3C, draw_param);
                break;
            }
            {
                s16 status_c8;
                u8 *status_c8_page;

                status_c8_page = (u8 *)0x80010000;
                status_c8 = status_c8_page[0x33C8];
                status_page = (u8 *)0x80010000;
                if (7 == status_c8) {
                    blit_origin_u16_block(0x40, 0xC, D_80127024, draw_param);
                }
                if (status_page[0x33C4] == 5) {
                    blit_origin_u16_block(0xE, 0xE, D_80126494, draw_param);
                }
            }
        } else if (draw_kind == 0x27) {
            s32 status_c4;
            u8 *status_c4_page;

            status_c4_page = (u8 *)0x80010000;
            status_c4 = status_c4_page[0x33C4];
            if (5 == status_c4) {
                blit_origin_u16_block(0x38, 0xE, D_80127FA8, draw_param);
            }
        }
        event_table = D_800D1910;
        event = entry_kind + event_table;
        if (event->field0 != 0) {
            set_texture_quad_32_uv(event->field0, event->field2,
                          event->field4, event->field5);
        }

        {
            u8 *draw_entry;
            s32 final_x;
            s32 final_y;
            s32 entry_offset;

            event = (Event6 *)town_map_selection_state;
            final_x = town_map_selection_state[0];
            final_y = ((u8 *)event)[1];
            entry_offset = ((u8 *)event)[6] << 5;
            draw_entry = town_map_variants + entry_offset;
            scale_coordinates_and_append_pointers(final_x, final_y,
                          draw_entry[4], draw_entry[5],
                          town_map_variants + entry_offset + 12);
        }
    }
    create_entry_builder_controller();
}
