#include "common.h"

#include "shared/gpu_packets.h"
#include "engine/graphics.h"
#include "shared/menu_display.h"
#include "engine/effect.h"






extern MenuDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* Initialize the object and its two data blocks from defaults, then apply starting settings. */
void init_gauge_blocks(void *unused, MenuDisplayNode *object,
                   MenuDisplayBlock *primary_data, DisplayPositionWords *secondary_data) {
    MenuDisplayBlock *primary_defaults = &display_block_defaults;
    DisplayPositionWords *secondary_defaults = &display_vector_defaults;
    s32 *secondary_first;

    primary_data->words[0] = primary_defaults->words[0];
    secondary_first = &secondary_defaults->unk0;
    primary_data->words[1] = primary_defaults->words[1];
    primary_data->words[2] = primary_defaults->words[2];
    primary_data->words[3] = primary_defaults->words[3];

    secondary_data->unk0 = *secondary_first;
    secondary_data->unk4 = secondary_defaults->unk4;
    secondary_data->unk8 = secondary_defaults->unk8;

    object->block = primary_data;
    object->vector = secondary_data;
    object->unk_00 = 0;

    object->block->fields.x = -0x6C;
    object->block->fields.y = -0x10;
    object->block->fields.mode = 4;
    set_color_components_and_scaled_fields(object, 0, 1);
}
