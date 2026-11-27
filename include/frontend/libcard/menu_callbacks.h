#ifndef FRONTEND_LIBCARD_MENU_CALLBACKS_H
#define FRONTEND_LIBCARD_MENU_CALLBACKS_H

#include "common.h"

struct CardSlotMenuState;

/* Memory-card menu action receiving the selected menu object; no return value. */
typedef void (*card_boot_menu_action_fn)(struct CardSlotMenuState *state);

/* Four-action memory-card menu table supplied by static data.
 * card_boot_dispatch_selected_menu_action copies it and indexes it with the selected command. */
typedef struct card_boot_menu_table {
    card_boot_menu_action_fn cb[4]; /* menu actions indexed by CardSlotMenuState.selected_command; each receives that object */
} card_boot_menu_table;

extern card_boot_menu_table card_boot_menu_actions;
void card_boot_begin_selected_slot_load(struct CardSlotMenuState *menu);
void card_boot_select_copy_source_slot(struct CardSlotMenuState *menu);
void card_boot_confirm_selected_slot_deletion(struct CardSlotMenuState *menu);

#endif
