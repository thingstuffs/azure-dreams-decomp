#include "modules/dungeon_engine_tile_map_fragment_b48c8.h"
#include "common.h"

/* Linked-list node with a next pointer at offset 0x0 and a 16-bit
 * flags/state field at offset 0x1E (shared shape with integrate_active_node_vectors's
 * D_80081498 view). */

/* D_80081498 is accessed via %hi/%lo, so its containing symbol must be
 * larger than the -G8 small-data threshold; pad it out. */
extern struct {
    ActiveNode *head;
    int pad[2];
} D_80081498;

extern s32 D_80012090[];


extern void clear_entry_flag_and_link_owner(void *entry);

/* Process nodes flagged 0x1000 and clear global bit 28 when D_80012090 is not 1. */
void process_flagged_nodes_and_clear_global_bit(void) {
    ActiveNode *node = D_80081498.head;

    if (node != 0) {
        do {
            if (node->field_1E & 0x1000) {
                clear_entry_flag_and_link_owner(node);
            }
            node = node->next;
        } while (node != 0);
    }
    if (*(s32 *)0x80012090 != 1) {
        D_800E296C &= 0xEFFFFFFF;
    }
}
