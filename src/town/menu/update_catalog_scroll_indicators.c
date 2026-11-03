#include "common.h"
#include "town/menu/catalog_parts.h"
#include "town/menu/catalog.h"


extern void **D_80129758[];
extern void **D_8012975C[];
extern u8 D_801285FC[];
extern u8 D_80128608[];

/* Set town slots from an active object's flags, or clear them when inactive. */
void update_catalog_scroll_indicators(CatalogDisplay *object)
{
    if (object->unk_0C != 0) {
        if (object->unk_0E & 1) {
            *D_80129758[0] = D_801285FC;
        }
        if (object->unk_0E & 2) {
            *D_8012975C[0] = D_80128608;
            return;
        }
    } else {
        ItemMenuPart **state = catalog_display_node_slots;

        state[12]->handler = 0;
        state[13]->handler = 0;
        state[26]->handler = 0;
        state[27]->handler = 0;
    }
}
