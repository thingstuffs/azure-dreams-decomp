#ifndef FRONTEND_LIBCARD_MESSAGE_H
#define FRONTEND_LIBCARD_MESSAGE_H
/* Prototypes of the functions defined in src/frontend/libcard/message/ (one true prototype each; maintained by tools/headers). */

#include "common.h"
#include "shared/gpu_packets.h"
#include "shared/menu_display.h"
#include "frontend/libcard/message_dialog.h"

struct Entity;
struct CardMessageDialogBody;
struct CardSaveMenuBody;
struct CardSaveHeadingDisplayPrefix;
struct CardDetailDisplayNode;
struct S_800491F4;

/* Byte index sequences stop at their node limit; complete bounds are unestablished. */
extern u8 card_message_chain_indices[];
extern u8 card_slot_chain_indices[];

/* card_boot_build_message_window_packets.c */
void *card_boot_build_message_window_packets(void *buffer, CardMessageDialogBody *layout);

/* card_boot_center_message_dialog_display.c */
void card_boot_center_message_dialog_display(CardMessageDialogBody *object);

/* card_boot_close_dialog_when_response_clears.c */
void card_boot_close_dialog_when_response_clears(struct CardMessageDialogBody *record);

/* card_boot_close_message_dialog.c */
s32 card_boot_close_message_dialog(s32 flagLinkedRecord);

/* card_boot_create_slot_window.c */
void *card_boot_create_slot_window(s32 parent_object, s32 object_index);

/* card_boot_initialize_dialog_draw_nodes.c */
void card_boot_initialize_dialog_draw_nodes(struct Entity *entity, s32 node_count);

/* card_boot_initialize_slot_window.c */
void card_boot_initialize_slot_window(void *record, s32 setup_value, s32 processing_value);

/* card_boot_layout_empty_slot_window.c */
void card_boot_layout_empty_slot_window(void *object);

/* card_boot_link_message_display_entries.c */
struct S_800491F4 *card_boot_link_message_display_entries(struct S_800491F4 **input);

/* card_boot_link_slot_window_entries.c */
void card_boot_link_slot_window_entries(struct S_800491F4 **value);

/* card_boot_measure_dialog_choice_word.c */
void card_boot_measure_dialog_choice_word(u8 *text, s32 word_index, s32 *offset_out, s32 *length_out, s32 *prior_chars_out);

/* card_boot_prepare_copy_destination_message.c */
void card_boot_prepare_copy_destination_message(void *context);

/* card_boot_release_five_message_entries.c */
void card_boot_release_five_message_entries(CardMessageDialogBody *record);

/* card_boot_release_three_row_panel_text.c */
void card_boot_release_three_row_panel_text(void *record);

/* card_boot_stop_slot_window_updates.c */
void card_boot_stop_slot_window_updates(void *record_data);

/* format_save_heading_text.c */
void format_save_heading_text(u8 *base_addr);

/* initialize_text_editor_context.c */
void initialize_text_editor_context(void *dest, s32 record_index);

/* release_three_row_panel_text.c */
void release_three_row_panel_text(struct CardSaveHeadingDisplayPrefix *object);

/* write_text_and_advance_selection.c */
void write_text_and_advance_selection(struct CardSaveMenuBody *menu);

/* Panel display records.  A panel copies the resident templates
 * display_block_defaults (one CardDisplayBlock, copied as four words) and
 * display_vector_defaults (one DisplayPositionWords) into its own storage,
 * links them from a node, and then places the block on screen. */
typedef MenuDisplayBlock CardDisplayBlock;
typedef MenuDisplayNode CardDisplayNode;

/* File-list panel: a heading node with its own block and vector, then 21 list
 * nodes that share one vector (init_card_file_list_panel, init_card_file_list_nodes). */
typedef struct CardFileListPanel {
    /* 0x000 */ s32 selection;
    /* 0x004 */ u8 pad_004[0x78];
    /* 0x07C */ s32 selected_slot;
    /* 0x080 */ u8 pad_080[0x70];
    /* 0x0F0 */ struct CardDetailDisplayNode *left;
    /* 0x0F4 */ struct CardDetailDisplayNode *right;
    /* 0x0F8 */ struct CardDetailDisplayNode *value;
    /* 0x0FC */ struct CardDetailDisplayNode *heading;
    /* 0x100 */ u8 pad_100[0xA04];
    /* 0xB04 */ CardDisplayBlock heading_block;
    /* 0xB14 */ DisplayPositionWords heading_vector;
    /* 0xB20 */ DisplayPositionWords vector;
    /* 0xB2C */ CardDisplayNode list_heading;
    /* 0xB3C */ CardDisplayNode *pointers[21];
    /* 0xB90 */ CardDisplayNode nodes[21];
    /* 0xCE0 */ CardDisplayBlock blocks[21];
} CardFileListPanel;

struct CardChoiceOwner;
struct CardContinueNodes;
struct CardSlotListNodes;
void card_boot_initialize_slot_window_frame(CardDisplayNode *entity, CardDisplayBlock *primary, DisplayPositionWords *secondary, s32 slot_index);
void init_card_choice_templates(CardDisplayNode *entry, CardDisplayBlock *block, DisplayPositionWords *vector);
void init_card_choice_nodes(struct CardChoiceOwner *owner, s32 count);
void init_card_continue_nodes(struct CardContinueNodes *owner, s32 count);
void init_card_slot_list_nodes(struct CardSlotListNodes *owner, s32 count);
void init_card_file_list_nodes(CardFileListPanel *owner, s32 count);
void init_card_continue_templates(CardDisplayNode *entry, CardDisplayBlock *block, DisplayPositionWords *vector);

/* Owner declarations appended by tools/headers (append-only; the lines above are hand-kept). */
struct CardContinueNodes;
void func_800237EC(struct CardContinueNodes *owner, s32 count);
void func_80024C70(struct CardFileListPanel *owner, s32 count);

#endif
