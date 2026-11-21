#include "common.h"
#include "frontend/libcard.h"
#include "frontend/card/server_imports.h"

/* Devkit panel renderer registered by the card constructors. */
s16 card_dev_render_panel_hierarchy(void) { return draw_tinted_node_sprites_scratch_8004DBDC(); }
