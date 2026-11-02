#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/menu_display.h"
#include "engine/text.h"

/* Template struct copied wholesale (word-by-word) into a1's target. */

/* Template struct copied wholesale (word-by-word) into a2's target. */


extern MenuDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* The live entity struct that a1 points at: same 16 bytes as S_8002E5D8's
   template, but the tail word(s) are reinterpreted/patched as smaller
   fields right after the template copy. */



/* Copy two templates into entity buffers, link them to the header, and apply defaults. */
void initialize_text_entity_templates(MenuDisplayNode *entity, MenuDisplayBlock *main_data, DisplayPositionWords *aux_data) {
    MenuDisplayBlock *main_template = &display_block_defaults;
    DisplayPositionWords *aux_template = &display_vector_defaults;
    s32 *aux_first_word;

    main_data->words[0] = main_template->words[0];
    aux_first_word = &aux_template->unk0;
    main_data->words[1] = main_template->words[1];
    main_data->words[2] = main_template->words[2];
    main_data->words[3] = main_template->words[3];

    aux_data->unk0 = *aux_first_word;
    aux_data->unk4 = aux_template->unk4;
    aux_data->unk8 = aux_template->unk8;

    entity->block = main_data;
    entity->vector = aux_data;
    entity->unk_00 = 0;

    entity->block->fields.x = -0xA0;
    entity->block->fields.y = -0x78;
    entity->block->fields.depth = 0x200;
    entity->block->fields.mode = 4;
}
