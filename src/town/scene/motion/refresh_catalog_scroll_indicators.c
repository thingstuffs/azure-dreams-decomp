#include "common.h"

typedef struct {
    u8 pad00[0xC];
    u8 active;
    u8 pad0D;
    u8 flags;
} TownObject;
extern void update_catalog_scroll_indicators(TownObject *);
/*
 * Refreshes the catalog arrows from the current scroll position with the supplied callback
 * arguments.
 */
void refresh_catalog_scroll_indicators(TownObject *object) { update_catalog_scroll_indicators(object); }
