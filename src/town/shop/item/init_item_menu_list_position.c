#include "common.h"
#include "town/shop/item.h"
#include "town/shop/item_menu_cursor_transition_g00601.h"
#include "town/shop/floating_number_widget_g00612.h"

/* Copies two templates into linked records and initializes position and offset vectors. */
void init_item_menu_list_position(ItemMenuTransition *vectors, ItemMenuDisplayLinks *config, s32 *position_data,
                   s32 *secondary_data, s32 x, s32 y) {
    const s32 *src0 = display_block_defaults.words;
    const DisplayPositionWords *src1 = &display_vector_defaults;
    s32 first_vector_word;

    position_data[0] = src0[0];
    position_data[1] = src0[1];
    position_data[2] = src0[2];
    first_vector_word = src1->unk0;
    position_data[3] = src0[3];
    secondary_data[0] = first_vector_word;
    secondary_data[1] = src1->unk4;
    secondary_data[2] = src1->unk8;
    config->position = (ItemMenuDisplayPosition *)secondary_data;
    config->display = (ItemMenuDisplayBlock *)position_data;
    config->unk_00 = 0;
    config->position->position.rotation_y = -0x400;
    config->display->x = x;
    config->display->y = y;
    config->display->depth = 0x400;
    config->display->mode = 4;
    vectors->start_x = x;
    vectors->start_y = y;
    vectors->unk_10.low = 0x400;
    if (x < 0) {
        vectors->unk_14.low = 0x30 - x;
    } else {
        vectors->unk_14.low = -0x60 - x;
    }
    vectors->unk_14.high = -0x40 - y;
    vectors->delta_z = -0x200;
}
