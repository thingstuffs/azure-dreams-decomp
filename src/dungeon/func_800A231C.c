#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 w2;
    u16 w4;
    u16 pad6;
    s32 value;
} DungeonRecord;


extern s32 D_800E0B54;

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 func_80099290(s8 *byte_ptr);
extern s32 append_typed_formatted_value(s32 *, s32);
extern void select_position_data_and_update_owner(void *entity, void *search_state);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 find_first_empty_floor_item_slot(void);
extern s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance);
struct DungeonDescriptor;
extern struct DungeonDescriptor * create_timed_effect_at_tile(s32 tile_x, s32 tile_y, s32 z, s32 *init_data);
extern s32 func_800A794C(s32, s32, s32, s32 *, s32, s32, s32);
extern s32 get_item_category_value(u8 *item);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

/* Registers an object at a resolved dungeon position or processes its fallback placement. */
s32 place_item_at_valid_floor_position(s32 x, s32 y, s32 z, s32 unused, s32 *object_data) {
    s16 tile_x;
    s16 tile_y;
    s16 tile_value;
    s32 output_start;
    s32 output_cursor;
    s16 x_short;
    s16 y_short;
    s16 z_short;

    x_short = (s16)x;
    y_short = (s16)y;
    z_short = (s16)z;
    if ((find_valid_floor_item_position(x_short, y_short, z_short,
                       &tile_x, &tile_y, &tile_value) << 16) != 0) {
        s16 record_index;
        DungeonRecord *record;

        record_index = find_first_empty_floor_item_slot();
        if (record_index >= 0) {
            if (func_800A794C(x_short, y_short, z_short, object_data,
                              tile_x, tile_y, tile_value) == 0) {
                ((s32 *)D_800E3548)[record_index] = *object_data;
                record = &((DungeonRecord *)D_800E36C8)[record_index];
                record->b0 = (u8)tile_x;
                record->b1 = (u8)tile_y;
                record->w4 = (u16)tile_value;
                record->w2 = (u16)tile_value;
                record->value = get_item_category_value(object_data);
                cycle_map_cell_flags(tile_x, tile_y, 0x800);
                select_position_data_and_update_owner(((u8 *)(&D_80082E80)), ((u8 *)D_800E3D7C));
            }
            return 1;
        }
    }

    create_timed_effect_at_tile(x_short, y_short, z_short, object_data);
    output_cursor = get_unused_text_buffer();
    output_start = output_cursor;
    output_cursor = append_typed_formatted_value(object_data, output_cursor);
    output_cursor = expand_text_control_codes(&D_800E0B54, output_cursor);
    func_80099290(output_cursor);
    display_text_with_fullwidth_adjustment(output_start);
    return 0;
}
