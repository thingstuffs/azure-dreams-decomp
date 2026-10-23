#include "common.h"

typedef struct {
    u8 pad00[0xC];
    u8 active;
    u8 pad0D;
    u8 flags;
} TownObject;
extern void update_catalog_scroll_indicators(TownObject *);
void update_catalog_scroll_secondary_object(TownObject *object) { update_catalog_scroll_indicators(object); }
