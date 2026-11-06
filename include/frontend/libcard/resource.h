#ifndef FRONTEND_LIBCARD_RESOURCE_H
#define FRONTEND_LIBCARD_RESOURCE_H
#include "frontend/libcard/save_menu.h"
#include "frontend/libcard/slot_menu.h"
struct Object_800128C8;
/* Prototypes of the functions defined in src/frontend/libcard/resource/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
struct ObjectNodeHeader;

/* card_boot_begin_selected_slot_load.c */
void card_boot_begin_selected_slot_load(void *state);

/* card_boot_finish_slot_load_and_change_scene.c */
void card_boot_finish_slot_load_and_change_scene(struct Object_800128C8 *object);

/* card_boot_highlight_selected_load_slot.c */
void card_boot_highlight_selected_load_slot(CardSaveMenuBody *state);

/* card_boot_load_selected_slot.c */
void card_boot_load_selected_slot(CardSlotMenuState *state);

/* card_boot_show_load_failure_notice.c */
void card_boot_show_load_failure_notice(struct ObjectNodeHeader *value);

#endif
