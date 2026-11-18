#include "common.h"
#include "shared/object_node.h"
#include "frontend/card/menu.h"

extern void release_devkit_node_handles(void *ptr);
extern void card_dev_create_save_screen(void *ptr);
extern void allocate_initializes(void *ptr, s32 value);

/* Releases the menu's handles and chooses a linked-object cleanup call from its stored value. */
void card_boot_clear_menu_state(void *ptr) {
    s32 value;

    release_devkit_node_handles(NODE_HEADER(ptr));
    value = *(s32 *)ptr;
    if (value == 0) {
        card_dev_create_save_screen(*(void **)((u8 *)ptr + 0x14));
        return;
    } else {
        allocate_initializes(*(void **)((u8 *)ptr + 0x14), value);
    }
}
