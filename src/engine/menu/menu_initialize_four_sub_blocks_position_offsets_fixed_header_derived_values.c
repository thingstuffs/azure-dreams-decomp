#include "common.h"
#include "engine/menu/animated_panel.h"
#include "shared/menu_display.h"
#include "engine/menu.h"

/*
 * Positions the first menu block relative to screen center (160, 128), binds the next three blocks
 * to header values, and initializes their fixed offsets plus the supplied half-extent.
 */
void menu_initialize_four_sub_blocks_position_offsets_fixed_header_derived_values(AnimatedMenuPanelBody *object, s32 x, s32 y, s16 extent)
{
    MenuDisplayBlock *block;
    s16 x_offset, y_offset;

    block = &object->elements[0].block;
    x_offset = (s16)(x - 0xA0);
    y_offset = (s16)(y - 0x80);
    object->elements[0].link.unk_00 = 0;
    block->fields.x = x_offset;
    block->fields.y = y_offset;
    block->fields.depth = 0x200;
    block->fields.mode = 4;

    block = &object->elements[1].block;
    object->elements[1].link.unk_00 = object->tag_values;
    block->fields.x = 0xC;
    block->fields.y = 0xE;

    block = &object->elements[2].block;
    object->elements[2].link.unk_00 = object->template_word;
    block->fields.x = extent / 2;
    block->fields.y = 8;

    block = &object->elements[3].block;
    object->elements[3].link.unk_00 = object->resource_handle;
    block->fields.x = 0x94;
    block->fields.y = 0x81;
}
