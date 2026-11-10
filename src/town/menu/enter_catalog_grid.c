#include "common.h"
#include "town/menu/catalog.h"
#include "m2c_compat.h"
#include "town/menu.h"

/* Update the controller and set its state to one. */
void enter_catalog_grid(CatalogDisplay *controller) {
    refresh_catalog_entry_grid(controller);
    controller->unk_0A = 1;
}
