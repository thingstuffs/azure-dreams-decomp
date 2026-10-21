#ifndef FRONTEND_LIBCARD_MENU_CALLBACKS_H
#define FRONTEND_LIBCARD_MENU_CALLBACKS_H

#include "common.h"

typedef void (*card_boot_menu_action_fn)(void *state);

typedef struct card_boot_menu_table {
    card_boot_menu_action_fn cb[4];
} card_boot_menu_table;

extern card_boot_menu_table D_800200A8;
void card_boot_begin_selected_slot_load(void *state);
void card_boot_select_copy_source_slot(void *state);
void card_boot_confirm_selected_slot_deletion(void *state);

#endif
