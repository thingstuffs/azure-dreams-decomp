#ifndef FRONTEND_CARD_MESSAGE_H
#define FRONTEND_CARD_MESSAGE_H
/* Prototypes of the functions defined in src/frontend/card/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

struct CardDevDialogDisplay;
struct ObjectNodeHeader;

/* Four pointers to encoded text in each devkit card layout row. */
extern u8 *card_layout_text_items[][4];

/* card_boot_build_four_layout_command_groups.c */
u8 *card_boot_build_four_layout_command_groups(u8 *buffer, struct CardDevDialogDisplay *layout);

/* card_boot_handle_menu_actions_and_repeat.c */
void card_boot_handle_menu_actions_and_repeat(void *menu);

/* card_boot_position_four_display_items.c */
void card_boot_position_four_display_items(struct CardDevDialogDisplay *state);

/* init_card_message_object_mode_seven.c */
void init_card_message_object_mode_seven(struct ObjectNodeHeader *value);
/* True-address alias for the MAIN card server placement at 0x804032FC. */
void initialize_card_message_object_with_code_7(struct ObjectNodeHeader *value);

/* init_card_message_object.c */
u8 *init_card_message_object(struct ObjectNodeHeader *message_param_1, s32 message_param_2, s32 message_param_3, s32 *result_slot);

/* store_first_coord.c */
void configure_card_grid_entry(void *object, s32 column, s32 mode, s32 row, s32 value);
/* True-address alias for the MAIN card server placement at 0x80402670. */
void position_object_record_and_update_row(void *object, s32 column, s32 mode, s32 row, s32 value);

#endif
