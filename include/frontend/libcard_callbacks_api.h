#ifndef FRONTEND_LIBCARD_CALLBACKS_API_H
#define FRONTEND_LIBCARD_CALLBACKS_API_H

#include "common.h"

struct CardDisplayNode;
struct CardSlotMenuState;
void card_boot_handle_slot_selection_input(struct CardSlotMenuState *object);
s16 card_boot_render_panel_hierarchy(s32 first_value, s32 second_value, struct CardDisplayNode *third_value);
void card_boot_restore_saved_selection_callback(void *object_data);
void card_boot_update_copy_destination_selection(u8 *menu);

#endif
