#ifndef FRONTEND_CARD_SERVER_IMPORTS_H
#define FRONTEND_CARD_SERVER_IMPORTS_H
/*
 * The devkit memory-card server (MAIN +0x269000-+0x275800, linked at 0x80400000; its assertion strings name the
 * file c_server.c) and the overlapping TOWN window (+0x26E000-+0x272000, linked at 0x80405000). The windows
 * share code at some addresses. The save callbacks at 0x80405A3C and 0x80405CB8 are present in MAIN.
 * This header declares calls to functions with no readable name at their address and the server's library stubs.
 *
 * The 0x804xxxxx entries are server functions.  Their rows are linked at the true address (rowbase records,
 * tools/headers/rebase_placeholder_rows.py), so the address spelling names the same symbol as the readable name
 * in the comment; the callers keep the address spelling because include/frontend/card.h types those prototypes
 * with generated layouts the devkit callers do not use. The named frame and slot helpers use their own
 * placed addresses. The 0x8003xxxx-0x8007xxxx entries are not
 * functions of the retail SLUS (mid-function or data): the server was linked against a devkit build of the
 * executable, so each is declared once here with its address spelling.
 *
 * foreign-program: main 0x269000-0x275800; town 0x26E000-0x272000
 */
#include "common.h"
struct CardDevDialogDisplay;
struct CardDevMenu10;
struct CardDevMenuEntry;
struct CardDisplayNode;
union CardDisplayBlock;
struct DisplayPositionWords;
struct CardBackgroundBody;
struct ObjectNodeHeader;

typedef struct CardSlotScreenEffect CardSlotScreenEffect;

struct CardChooserBody;
void release_devkit_node_handles(struct ObjectNodeHeader *node);
void release_card_screen_parts(struct ObjectNodeHeader *node);
void assert_card_slot_and_set_high_bit(struct ObjectNodeHeader *slot);
void set_record_values(struct CardChooserBody *menu, struct ObjectNodeHeader *request, s32 mode);
CardSlotScreenEffect *create_card_dev_slot_screen_effect(struct ObjectNodeHeader *request, s32 mode);

/* Card grid mode is set for the whole row before the selected entries. */
struct CardDevRowEntry;
void set_card_grid_row_mode_80051DE4(struct CardDevRowEntry *entries, s32 mode);
void set_card_grid_entry_mode_800514A8(struct CardDevRowEntry *entry, s32 mode);
/* devkit executable: release one text word (the card UI's own build calls noop_release_notification here) */
void func_80051FBC(s32 value);

/* server functions at their true addresses */
s32 card_dev_event_ioe_handler_804009C0(void);
s32 card_dev_event_error_handler_804009D4(void);
s32 card_dev_event_timeout_handler_804009E8(void);
s32 card_dev_event_new_handler_804009FC(void);
void process_four_referenced_values(void *object);   /* placed fade_four_entries at 0x804033EC */
struct CardDevFadeRefs;
void card_dev_fade_four_values(struct CardDevFadeRefs *object);
struct CardDevDialogDisplay;
/* server addresses 0x80402CD4 and 0x80402BB8, called by the dialog object's initializer */
void *initialize_four_paired_drawing_records(void *buffer, struct CardDevDialogDisplay *dialog);
void position_linked_dialog_and_bind_object_data(struct CardDevDialogDisplay *dialog);
struct CardDevCommandPanel;
void card_dev_initialize_command_panel(struct CardDevCommandPanel *panel, struct ObjectNodeHeader *owner);
void card_dev_init_row_panel(struct CardDevCommandPanel *panel);
void card_dev_set_word(struct CardDevCommandPanel *panel, struct ObjectNodeHeader *owner);   /* card_dev_set_word */
void func_80404708(void *templates, void *primary, void *secondary);
void card_background_init_components(struct CardBackgroundBody *record);   /* card_background_init_components */
void card_background_set_word(struct CardBackgroundBody *record, struct ObjectNodeHeader *owner);   /* card_background_set_word */
void func_80402974(struct CardDisplayNode *templates, union CardDisplayBlock *primary, struct DisplayPositionWords *secondary);   /* card_dev_init_view_defaults */
void init_dialog_object(struct CardDevDialogDisplay *record);   /* init_dialog_object */
void func_80403DA0(struct CardDevMenuEntry *entry, union CardDisplayBlock *placement, s32 *settings, s32 slot_index);   /* card_dev_init_row_view */
void func_80404254(struct CardDevMenu10 *record, s32 entry_count);
void card_dev_initialize_slot_window(struct CardDevMenu10 *record, struct ObjectNodeHeader *owner, s32 slot_index);
void card_dev_layout_selected_slot_entries(struct CardDevMenu10 *window);
void set_layout_params(struct CardDevDialogDisplay *record, struct ObjectNodeHeader *owner, s32 entry_index, s32 value_0c, s32 *result_slot);   /* set_layout_params */
void card_dev_set_slot_index_and_owner(struct CardDevMenu10 *record, struct ObjectNodeHeader *owner, s32 slot_index);   /* the server copy of card_boot_set_slot_index_and_owner */

/* Imported declarations, one per address. */
void func_8003830C(s32, void *);
void *allocate_card_object_8003C480(s32 mode);
void *func_8003C714(s32, void *, s32);
void request_scene_dispatch_state_8003D548(s32 state);
void card_diagnostic_printf_8003FA78(const char *format, ...);
void begin_card_chooser_exit_transition_8003FD58(s32, s32, s32, s32);
void func_80040560(void *, void *);
s32 func_80047358(void *entries, void *template_data, s32 entry_count);
s32 func_80047938(void *, s32, s32);
s32 func_80047FD8(void *);
s32 func_800484A4(s32, s32 *);
s16 draw_tinted_node_sprites_scratch_8004DBDC(void);
struct CardDevMenu4;
struct CardDevLoadNode;
s32 dispatch_context_through_four_entry_table(struct CardDevMenuEntry **entries);
struct CardDevSlotMenu;
void assert_slot_store_value_and_process_state(struct ObjectNodeHeader *node, s32 selection);
void update_embedded_selected_slot_outputs(struct ObjectNodeHeader *node, s32 *enabled, s32 *selected);
void update_two_slots_using_selection_mapping(struct CardDevSlotMenu *panel);
void initialize_child(struct CardDevSlotMenu *panel);
void initialize_two_positioned_object_entries(struct CardDevSlotMenu *panel);
void card_dev_init_slot_entry_tables(struct CardDevSlotMenu *panel, s32 count);
void func_80407688(struct CardDevSlotMenu *panel, struct ObjectNodeHeader *owner);
struct FrameState;
s32 advance_timed_tagged_stream_8004DCCC(struct FrameState *cursor);
struct FrameNode;
void initialize_scaled_entry_cursor_8004DDBC(struct FrameState *cursor, struct FrameNode *entry, s32 *output);
s32 build_positioned_text_glyphs_80051520(void *, s32 *, s32);
void func_80051804(s32, s32, s32 *);
void format_int_zero_padded_8005184C(s32, s32, void *);
void func_80051898(u32, void *);
void remap_flagged_string_bytes_80051900(s32 *);
s32 func_80051B50(void *, s32, s32);
s32 step_card_menu_selection_80056450(s32 index, s32 step, u8 limit);
s32 func_80056F14(s32);
s32 advance_card_menu_index_80058FF0(s32 index, s32 delta, s32 limit);
void SD_Call_80063FF8(s32 command);
s32 VSync_800702F0(s32 mode);
u16 GetTPage_80078570(s32 depth, s32 blend, s32 x, s32 y);
u16 GetClut_80078640(s32 x, s32 y);
/* Devkit libc stubs. The string builders still share byte and word buffer views. */
void exit_8007BEF0(s32 status) __attribute__((noreturn));
void puts_8007BF18(const char *message);
void func_8007BF50(void *, const void *);
void func_8007BF80(void *, const char *);
void bzero_8007BFE0(void *buffer, s32 size);
s32 printf_8007C040(const char *format, ...);
/* Devkit BIOS backup initialization and event stubs. */
void _bu_init_8007C958(void);
s32 OpenEvent_8007C998(u32 event_class, s32 spec, s32 mode, s32 (*callback)(void));
s32 CloseEvent_8007C9A8(s32 event);
s32 TestEvent_8007C9C8(s32 event);
s32 EnableEvent_8007C9D8(s32 event);
void EnterCriticalSection_8007CA38(void);
void ExitCriticalSection_8007CA48(void);
/* Devkit file stubs, at a common +0x129B4 offset from the resident SDK stubs. */
s32 open_8007CA58(s32 path_address, s32 flags);
s32 lseek_8007CA68(s32 file, s32 offset, s32 origin);
s32 read_8007CA78(s32 file, void *buffer, s32 size);
s32 write_8007CA88(s32 file, void *buffer, s32 size);
void close_8007CA98(s32 file);
void format_8007CAA8(const char *device);
struct DevCardDirectoryEntry;
s32 firstfile2_8007CAB8(const char *pattern, struct DevCardDirectoryEntry *entry);
struct DevCardDirectoryEntry *nextfile_8007CAC8(struct DevCardDirectoryEntry *entry);
void rename_8007CAD8(const char *old_path, const char *new_path);
void erase_8007CAE8(const char *path);
void ChangeClearPAD_8007CB08(s32 mode);
/* the server's own libcard BIOS stubs (config/names.tsv: address-suffixed, the plain names are the SLUS stubs) */
s32 _card_status_80408644(s32);
void _card_wait_80408654(s32);
s32 _card_info_80408664(s32);
s32 _card_load_80408674(s32);
s32 _card_write_804086BC(s32, s32, s32);
void _new_card_804086CC(s32);
void _ExitCard_804087C8(void);
void install_card_bios_patch_804088A0(void);
void swap_card_bios_patch_80408958(void);
/* the server's libcard entries (assembler rows linked at their placeholder; callers jal the true address) */
void InitCARD2_80408798(s32);
void StartCARD2_804087A8(void);
void StopCARD2_804087B8(void);
/* --- end of imports --- */

#endif
