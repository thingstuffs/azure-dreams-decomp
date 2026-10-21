#ifndef FRONTEND_CARD_MESSAGE_H
#define FRONTEND_CARD_MESSAGE_H
/* Prototypes of the functions defined in src/frontend/card/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct S_80402A1C_0;

/* card_boot_build_four_layout_command_groups.c */
void *card_boot_build_four_layout_command_groups(void *buffer, struct S_80402A1C_0 *layout);

/* card_boot_handle_menu_actions_and_repeat.c */
void card_boot_handle_menu_actions_and_repeat(void *menu);

/* card_boot_position_four_display_items.c */
void card_boot_position_four_display_items(u8 *state);

/* check_record_field_is_one.c */
void check_record_field_0x04_is_one(s32 value);

/* init_card_message_object.c */
u8 *init_card_message_object(s32 message_param_1, s32 message_param_2, s32 message_param_3, s32 message_param_4);

/* store_first_coord.c */
void configure_card_grid_entry(void *object, s32 column, s32 mode, s32 row, s32 value);

#endif
