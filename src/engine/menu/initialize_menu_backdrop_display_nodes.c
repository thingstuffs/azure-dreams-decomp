#include "common.h"
#include "shared/gpu_packets.h"
#include "engine/menu.h"

extern SevenEntryMenuBackdropDisplayBlock display_block_defaults;
extern DisplayPositionWords display_vector_defaults;

/* Initializes menu backdrop nodes, their pointer table and shared position from the display defaults. */
void initialize_menu_backdrop_display_nodes(SevenEntryMenuBackdropBody *body, s32 node_count)
{
    s32 i;
    s32 w0;

    for (i = 0; i < node_count; i++) {
        w0 = display_block_defaults.words[0];
        body->view.initializer.node_pointers[i] = &body->view.initializer.nodes[i];
        body->view.initializer.blocks[i].words[0] = w0;
        body->view.initializer.blocks[i].words[1] = display_block_defaults.words[1];
        body->view.initializer.blocks[i].words[2] = display_block_defaults.words[2];
        body->view.initializer.blocks[i].words[3] = display_block_defaults.words[3];
        body->view.initializer.nodes[i].display_block = &body->view.initializer.blocks[i];
        body->view.initializer.nodes[i].position = &body->display_position;
    }
    body->display_position.unk0 = display_vector_defaults.unk0;
    body->display_position.unk4 = display_vector_defaults.unk4;
    body->display_position.unk8 = display_vector_defaults.unk8;
}
