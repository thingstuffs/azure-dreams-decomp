#include "modules/town_map_props.h"
#include "town/scene/list_setup.h"
#include "shared/game_work.h"
#include "town/person/position.h"
typedef union
{
    s32 coord;
    u8 *object;
}
CoordOrObject;
typedef union
{
    s32 w[5];
    s16 h[10];
}
SpBuf;
extern void strcpy(void *, s32);
extern s32 strlen(void *);
extern s16 dir_step_x[][2];
extern s16 dir_step_y[][2];
extern u8 *D_80073600[];
extern s32 D_800D2134[][2];
extern s32 D_800D214C[][2];
extern s32 D_800D215C[];
extern s32 D_800D216C[][2];
extern s32 town_item_layout_coordinates[][3];
extern s32 D_800D21B4[];
extern s8 D_800D2238[];
extern u8 D_800D225C[];
extern u8 D_80112070[];
extern void strcpy(void *, s32);
extern s32 strlen(void *);

/* town_map_mod_yorozu_item: Creates a town object by type and initializes its position and display data. */
void town_map_mod_yorozu_item(s16 *tile_data, s16 object_type, s32 spawn_value)
{
    SpBuf position;
    s16 type_index;
    s16 direction;
    s32 spawn_param;
    CoordOrObject x_or_object;
    CoordOrObject y_or_state;
    s32 *object_state;
    s32 *variant_row;
    s32 shifted_type_index;
    s32 part_index;
    s32 entry_index;
    u16 display_flags;
    u16 alt_display_flags;
    u8 *display_data;
    u8 *name_buffer;
    entry_index = 0;
    spawn_param = spawn_value;
    type_index = object_type - 1;
    shifted_type_index = type_index << 16;
    x_or_object.coord = tile_data[0] + 8;
    y_or_state.coord = tile_data[1] + 8;
    position.w[2] = -0x800000;
    switch (shifted_type_index >> 16) {
    case 0:
    case 1:
        apply_item_and_update_matching_actor_state((s16)x_or_object.coord, (s16)y_or_state.coord, object_type, (s16)spawn_param);
        return;

    case 7:
        fill_wrapped_four_by_four_grid((s16)x_or_object.coord, (s16)y_or_state.coord, (s16)spawn_param);
        return;

    case 15:
        entry_index++;

    case 14:
        entry_index++;

    case 13:
        direction = tile_data[3];
        if (direction < 2) {
            x_or_object.coord++;
        }
        if (direction == 1) {
            y_or_state.coord++;
        }
        position.w[0] = ((x_or_object.coord << 6) - (dir_step_y[direction][0] << 3)) << 16;
        position.w[1] = ((y_or_state.coord << 6) + (dir_step_x[direction][0] << 3)) << 16;
        position.w[2] = 0;
        variant_row = D_800D2134[entry_index];
        x_or_object.object = create_positioned_visual_object(position.w, update_record_output_grid, direction << 10, *variant_row);
        y_or_state.object = x_or_object.object + 0x20;
        *((s32 **) (y_or_state.object + 0xA0)) = variant_row;
        break;

    case 5:
        entry_index++;

    case 6:
        part_index = 1;
        position.w[0] = x_or_object.coord << 22;
        position.w[1] = y_or_state.coord << 22;
        position.w[2] = -0x80000;
        do {
            create_positioned_visual_object(position.w, no_op_effect_callback, 0, D_800D214C[entry_index][part_index]);
            part_index--;
        }
        while (part_index >= 0);
        return;

    case 8:
    {
        entry_index = 3;
        position.w[0] = x_or_object.coord << 22;
        position.w[1] = y_or_state.coord << 22;
        position.w[2] = -0x80000;
        do {
            create_positioned_visual_object(position.w, no_op_effect_callback, 0, D_800D215C[entry_index]);
            entry_index--;
        }
        while (entry_index >= 0);
        position.w[0] = (x_or_object.coord << 22) + 0x01000000;
        position.w[1] = (y_or_state.coord << 22) + 0x01600000;
        position.h[5] = 0;
        {
            s32 shifted_type = object_type << 16;
            u8 *type_table = (u8 *) D_800D21B4;
            x_or_object.object = create_positioned_graphic_object_2(position.w, no_op_effect_callback, *((s32 *) (type_table + (shifted_type >> 14))));
        }
        y_or_state.object = x_or_object.object + 0x20;
        *((s16 *) (((u8 *) (*((void **) (x_or_object.object + 0xC)))) + 6)) = 0x18;
        break;
    }

    case 3:
    case 9:
    case 16:
    case 29:
    case 30:
        position.w[0] = (x_or_object.coord << 22) + 0x200000;
        position.w[1] = (y_or_state.coord << 22) + 0x200000;
        position.h[5] = query_lowered_transform_position(position.w);
        if (position.w[2] > 0) {
            position.w[2] = 0;
        }
        x_or_object.object = create_positioned_graphic_object_2(position.w, no_op_effect_callback, D_800D21B4[object_type]);
        y_or_state.object = x_or_object.object + 0x20;
        if (object_type == 0xA) {
            display_data = *((void **) (x_or_object.object + 0xC));
            *((s16 *) (((u8 *) display_data) + 6)) = 0x20;
        }
        break;

    case 19:
        entry_index++;

    case 18:
        entry_index++;

    case 21:
        entry_index++;

    case 4:
        entry_index++;

    case 2:
        position.w[0] = (x_or_object.coord << 22) + 0x200000;
        position.w[1] = (y_or_state.coord << 22) + 0x200000;
        position.h[5] = query_lowered_transform_position(position.w);
        x_or_object.object = create_positioned_graphic_object_2(position.w, initialize_record_visual_state, D_800D21B4[(s16) object_type]);
        y_or_state.object = x_or_object.object + 0x20;
        *((s32 *) (y_or_state.object + 0xA0)) = D_800D216C[entry_index][0];
        *((s32 *) (y_or_state.object + 0xA4)) = D_800D216C[entry_index][1];
        if (object_type == 0x13) {
            display_data = *((void **) (x_or_object.object + 0xC));
            display_flags = *((u16 *) (((u8 *) display_data) + 0x14));
            *((s16 *) (((u8 *) display_data) + 0x10)) = 0;
            *((u16 *) (((u8 *) display_data) + 0x14)) = display_flags | 0xC;
        }
        break;

    case 20:
        entry_index++;

    case 22:
        position.w[0] = (x_or_object.coord << 22) + 0x200000;
        position.w[1] = (y_or_state.coord << 22) + 0x200000;
        position.h[5] = query_lowered_transform_position(position.w);
        x_or_object.object = create_positioned_graphic_object_2(position.w, copy_record_state_to_destination, D_800D21B4[(s16) object_type]);
        y_or_state.object = x_or_object.object + 0x20;
        *((s32 *) (y_or_state.object + 0xA0)) = town_item_layout_coordinates[entry_index][0];
        *((s32 *) (y_or_state.object + 0xA4)) = town_item_layout_coordinates[entry_index][1];
        *((s32 *) (y_or_state.object + 0xA8)) = town_item_layout_coordinates[entry_index][2];
        if (object_type == 0x17) {
            display_data = *((void **) (x_or_object.object + 0xC));
            alt_display_flags = *((u16 *) (((u8 *) display_data) + 0x14));
            *((s16 *) (((u8 *) display_data) + 0x10)) = 0x20;
            *((u16 *) (((u8 *) display_data) + 0x14)) = alt_display_flags | 0xC;
        }
        break;

    case 17:
        position.w[0] = (x_or_object.coord << 22) + 0x200000;
        position.w[1] = (y_or_state.coord << 22) + 0x200000;
        position.h[5] = query_lowered_transform_position(position.w);
        {
            s32 shifted_type = object_type << 16;
            u8 *type_table = (u8 *) D_800D21B4;
            x_or_object.object = create_positioned_graphic_object_2(position.w, advance_actor_animation_pose, *((s32 *) (type_table + (shifted_type >> 14))));
        }
        y_or_state.object = x_or_object.object + 0x20;
        *((s32 *) (y_or_state.object + 0xA0)) = position.h[5];
        break;

    default:
        return;
    }

    name_buffer = D_80112070 + (object_type * 0x82);
    strcpy(name_buffer, *((s32 *) ((D_80073600[0] + (object_type * 0x14)) + 8)));
    entry_index = strlen(name_buffer);
    name_buffer[entry_index] = 0x11;
    entry_index++;
    name_buffer[entry_index] = 1;
    *((void **) (((u8 *) y_or_state.object) + 0x48)) = name_buffer;
    object_state = (s32 *) y_or_state.object;
    configure_the_set_mode_n_1(object_state, *((void **) (x_or_object.object + 8)), D_800D225C + (D_800D2238[object_type] * 0x18));
}
