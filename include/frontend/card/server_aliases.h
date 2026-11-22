#ifndef FRONTEND_CARD_SERVER_ALIASES_H
#define FRONTEND_CARD_SERVER_ALIASES_H
/*
 * Devkit memory-card server (MAIN +0x269000, linked at 0x80400000): functions whose C row is still linked at its
 * 0x8001xxxx placeholder row id, reached by the server's callers at the true address. The aliases in
 * config/names.tsv bind those calls to the server placement.
 */
#include "common.h"
#include "frontend/card/service/selected_channel_data.h"
struct ObjectNodeHeader;
struct CardDevMenu4;

/* row main/func_8001C25C at 0x8040325C */
void initialize_card_message_object_with_code_0xb(void *object);

/* card_dev_run_temp_slot_operation (row main/func_8001B3C4) at 0x804023C4 */
void run_slot_operation_code_five(void);

/* clear_global_if_value_zero (row main/func_8001B93C) at 0x8040293C */
struct S_8001B93C_0;
void call_handler_with_zero_if_field_is_zero(struct S_8001B93C_0 *object);
/* refresh_card_message_object (row main/func_8001C43C) at 0x8040343C */
s32 process_global(s32 flag_linked_object);

/* release_card_screen_parts at 0x80406720 */
void propagate_object_high_bit_flags(void *object);

/* Server functions at their true addresses. */
s32 card_devkit_poll_hardware_status_8040153C(void);                 /* hardware-status poll */
struct CardSaveOperationBody;
void card_dev_poll_save_result_and_resume_menu_input(struct CardSaveOperationBody *record_data);
void func_80405A64(void *record_data);   /* Same placement, retained by the save factories. */
void card_dev_enter_copying_progress(void *record_data);
void card_dev_set_save_menu_slot_mode(void *menu);         /* set save-menu words at +0x48 and +0x4C */
void card_dev_enter_saving_progress(void *record_data);
void card_dev_enter_load_overwrite_confirmation(void *record_data);
void install_pending_load_completion_callback(void *record_data);
void card_dev_enter_overwrite_space_advice(void *record_data);
void card_dev_enter_card_space_advice(void *record_data);
void card_dev_refresh_info_object(void *part);
void card_dev_refresh_sme_object(void *part);
void card_dev_refresh_slot_window(void *part);
struct CardDevLoadNode;
void card_dev_prepare_save_heading_layout(struct CardDevMenu4 *state, struct CardDevLoadNode *owner); /* the server copy of prepare_save_heading_layout */

/* the card UI dirty word (0x8008DAB4) as the server's load-screen release reads and writes it: one scalar word
 * (its other users still declare their own array views locally) */
extern s32 card_ui_dirty_flags;

#endif
