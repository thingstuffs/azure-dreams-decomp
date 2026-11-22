#include "common.h"
#include "frontend/card/server_imports.h"
#include "shared/object_node.h"
#include "frontend/card/save.h"
#include "frontend/card/load.h"
#include "frontend/card/menu.h"


/* Releases the menu's handles and chooses a linked-object cleanup call from its stored value. */
void card_boot_clear_menu_state(CardChooserBody *menu) {
    s32 value;

    release_devkit_node_handles(NODE_HEADER(menu));
    value = menu->mode;
    if (value == 0) {
        card_dev_create_save_screen(menu->request);
        return;
    } else {
        allocate_initializes(menu->request, value);
    }
}
