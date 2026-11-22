#include "shared/menu_display.h"
#include "town/shop/storage_menu.h"


typedef struct {
    u8 byte0;
    u8 byte1;
    u8 byte2;
} DisplayPrefix;

typedef struct {
    s32 unused;
    DisplayPrefix *display;
} DisplayPrefixLinks;

/* Copy the display templates into the storage object and bind its links. */
void initialize_entity_display_parts(ItemMenuDisplayLinks *links, StorageDisplayBlock *part, ItemMenuDisplayPosition *vector) {
    s32 *part_template = display_block_defaults.words;
    DisplayPositionWords *vector_template = &display_vector_defaults;
    s32 *vector_word;
    DisplayPrefixLinks *prefix_links = (DisplayPrefixLinks *)links;

    part->words[0] = part_template[0];
    vector_word = &vector_template->unk0;
    part->words[1] = part_template[1];
    part->words[2] = part_template[2];
    part->words[3] = part_template[3];

    vector->words.unk0 = *vector_word;
    vector->words.unk4 = vector_template->unk4;
    vector->words.unk8 = vector_template->unk8;

    links->display = &part->display;
    links->position = vector;
    links->unk_00 = 0;

    prefix_links->display->byte0 = 0;
    prefix_links->display->byte1 = 0;
    prefix_links->display->byte2 = 0;
    links->display->x = 0;
    links->display->y = 0;
    links->display->depth = 0x200;
    links->display->ramp = 0x1000;
    links->position->position.offset_y = 0x30;
    links->display->mode = 4;
}
