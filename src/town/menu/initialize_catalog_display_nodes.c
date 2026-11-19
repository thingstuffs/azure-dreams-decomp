#include "common.h"
#include "m2c_compat.h"
#include "town/menu/catalog.h"
#include "shared/item_menu.h"
#include "town/menu/catalog_parts.h"
#include "engine/graphics.h"
#include "town/menu.h"


#ifndef NULL
#define NULL 0
#endif

extern ItemMenuPart D_801298B8[98];
extern ItemMenuPartPosition D_80129ED8[98];
extern DisplayPositionWords D_8012A4F8[98];



/* Initializes 98 linked nodes and attaches their table to the context. */
s32 initialize_catalog_display_nodes(CatalogDisplay *context) {
    ItemMenuPart **node_slot;
    ItemMenuPart *node;
    ItemMenuPartPosition *node_data;
    DisplayPositionWords *node_aux;
    ItemMenuPart *prev_node;
    s32 node_count;
    s32 result;

    prev_node = NULL;
    node_count = 0;
    node_slot = catalog_display_node_slots;
    node_aux = D_8012A4F8;
    node_data = D_80129ED8;
    node = D_801298B8;
    do {
        *node_slot = node;
        node->position = node_data;
        node_data += 1;
        node += 1;
        node_count += 1;
        (*node_slot)->vector = node_aux;
        node_aux += 1;
        (*node_slot)->next = prev_node;
        prev_node = *node_slot;
        node_slot += 1;
    } while (node_count < 0x62);
    apply_display_block_defaults(catalog_display_node_slots, 0x62);
    apply_display_vector_defaults(catalog_display_node_slots, 0x62);
    context->parts.nodes = catalog_display_node_slots;
    context->last_node = catalog_display_node_slots[97];
    result = 1;
    return result;
}

/* MECHANISM: The natural loop shape yields the exact 32-byte frame and s1/s0/ra saves. */
