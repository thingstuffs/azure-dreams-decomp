#include "common.h"
#include "shared/menu_display.h"
#include "frontend/libcard/message.h"

/* Initialize entity nodes with template data and link them to shared common data. */
void card_boot_initialize_dialog_draw_nodes(CardMessageDialogBody *entity, s32 node_count)
{
    s32 i;
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;

    for (i = 0; i < node_count; i++) {
        w0 = display_block_defaults.words[0];
        entity->entries[i] = &entity->nodes[i].display;
        entity->blocks[i].words[0] = w0;
        w1 = display_block_defaults.words[1];
        entity->blocks[i].words[1] = w1;
        w2 = display_block_defaults.words[2];
        entity->blocks[i].words[2] = w2;
        w3 = display_block_defaults.words[3];
        entity->nodes[i].display.block = &entity->blocks[i];
        entity->nodes[i].vector = &entity->vector;
        entity->blocks[i].words[3] = w3;
    }
    entity->vector.unk0 = display_vector_defaults.unk0;
    entity->vector.unk4 = display_vector_defaults.unk4;
    entity->vector.unk8 = display_vector_defaults.unk8;
}
