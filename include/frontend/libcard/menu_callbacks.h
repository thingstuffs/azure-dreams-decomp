#ifndef FRONTEND_LIBCARD_MENU_CALLBACKS_H
#define FRONTEND_LIBCARD_MENU_CALLBACKS_H

#include "common.h"

/* Memory-card menu action receiving the selected menu object; no return value. */
typedef void (*card_boot_menu_action_fn)(void *state);

/* Four-action memory-card menu table supplied by static data.
 * card_boot_dispatch_selected_menu_action copies it and indexes it with the object callback selector. */
typedef struct card_boot_menu_table {
    card_boot_menu_action_fn cb[4]; /* menu actions indexed by the object selector at +0x44; each receives that object */
} card_boot_menu_table;

extern card_boot_menu_table D_800200A8;
void card_boot_begin_selected_slot_load(void *state);
void card_boot_select_copy_source_slot(void *state);
void card_boot_confirm_selected_slot_deletion(void *state);

#endif
