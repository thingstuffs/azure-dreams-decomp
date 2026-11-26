#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"

void *initialize_consecutive();                         /* extern */
typedef struct MainPacket12 MainPacket12;
MainPacket12 *initialize_drawing();                         /* extern */

/* Process four embedded components, then the containing object. */
void card_background_init_components(CardBackgroundBody *object) {
    initialize_consecutive(object->first_packets);
    card_background_init_overlay_prims(object->alternate_packets);
    card_background_init_selected_prims(object->selected_packets);
    initialize_drawing(object->shared_packets);
    card_background_layout_entries(object);
}
