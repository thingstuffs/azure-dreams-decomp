#ifndef FRONTEND_LIBCARD_RESOURCE_H
#define FRONTEND_LIBCARD_RESOURCE_H
/* Prototypes of the functions defined in src/frontend/libcard/resource/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* card_boot_begin_selected_slot_load.c */
void card_boot_begin_selected_slot_load(void *state);

/* card_boot_finish_slot_load_and_change_scene.c */
void card_boot_finish_slot_load_and_change_scene(void *object);

/* card_boot_highlight_selected_load_slot.c */
void card_boot_highlight_selected_load_slot(void *state);

/* card_boot_load_selected_slot.c */
void card_boot_load_selected_slot(s8 *state);

/* card_boot_show_load_failure_notice.c */
void card_boot_show_load_failure_notice(s32 value);

#endif
