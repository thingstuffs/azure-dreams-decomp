#include "common.h"
#include "frontend/card.h"
#include "shared/menu_display.h"
#include "frontend/card/menu_defaults.h"

/* Copy the display templates and place the command-panel frame at (-152, -98). */
void card_dev_init_command_panel_frame(MenuDisplayNode *node, MenuDisplayBlock *block, DisplayPositionWords *vector)
{
    s32 first_setting;

    block->words[0] = menu_primitive_defaults[0];
    first_setting = menu_settings_defaults[0];
    block->words[1] = menu_primitive_defaults[1];
    block->words[2] = menu_primitive_defaults[2];
    block->words[3] = menu_primitive_defaults[3];
    vector->unk0 = first_setting;
    vector->unk4 = menu_settings_defaults[1];
    vector->unk8 = menu_settings_defaults[2];
    node->block = block;
    node->vector = vector;
    node->draw_commands = 0;
    node->block->fields.x = -152;
    node->block->fields.y = -98;
    node->block->fields.depth = 512;
    node->block->fields.mode = 4;
}
