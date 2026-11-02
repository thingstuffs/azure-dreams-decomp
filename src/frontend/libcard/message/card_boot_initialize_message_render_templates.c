#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/menu_display.h"
#include "frontend/libcard/message.h"


extern MenuDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;



/* Copy and link entity templates, clear its state, and set primary field defaults. */
void card_boot_initialize_message_render_templates(MenuDisplayNode *entity, MenuDisplayBlock *primary_data, DisplayPositionWords *secondary_data) {
    MenuDisplayBlock *primary_template = &display_block_defaults;
    DisplayPositionWords *secondary_template = &display_vector_defaults;
    s32 *secondary_head;

    primary_data->words[0] = primary_template->words[0];
    secondary_head = &secondary_template->unk0;
    primary_data->words[1] = primary_template->words[1];
    primary_data->words[2] = primary_template->words[2];
    primary_data->words[3] = primary_template->words[3];

    secondary_data->unk0 = *secondary_head;
    secondary_data->unk4 = secondary_template->unk4;
    secondary_data->unk8 = secondary_template->unk8;

    entity->block = primary_data;
    entity->vector = secondary_data;
    entity->unk_00 = 0;

    entity->block->fields.x = -0xA0;
    entity->block->fields.y = -0x48;
    entity->block->fields.depth = 0x200;
    entity->block->fields.mode = 4;
}
