#include "common.h"
#include "engine/graphics.h"
#include "shared/menu_display.h"

/* Struct for the global D_8002E5D8: a 16-byte record copied field-by-field
   into each entry's target sub-struct. */

extern MenuDisplayBlock display_block_defaults;

/* Entry type: nodes points to an array of pointers to these nodes.
   unk4 is a pointer to a 16-byte record that gets overwritten with
   the contents of D_8002E5D8. */
typedef struct S_8004CC38_Node {
    void *unk0;
    MenuDisplayBlock *unk4;
} S_8004CC38_Node;

/*
 * Copies all four words of display_block_defaults into each node target when the node count is
 * positive.
 */
void apply_display_block_defaults(S_8004CC38_Node **nodes, s32 node_count) {
    s32 node_index;

    node_index = 0;
    if (node_count > 0) {
        do {
            (*nodes)->unk4->words[0] = display_block_defaults.words[0];
            (*nodes)->unk4->words[1] = display_block_defaults.words[1];
            (*nodes)->unk4->words[2] = display_block_defaults.words[2];
            node_index += 1;
            (*nodes)->unk4->words[3] = display_block_defaults.words[3];
            nodes += 1;
        } while (node_index < node_count);
    }
}
