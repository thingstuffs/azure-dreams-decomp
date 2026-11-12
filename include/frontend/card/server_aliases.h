#ifndef FRONTEND_CARD_SERVER_ALIASES_H
#define FRONTEND_CARD_SERVER_ALIASES_H
/*
 * Devkit memory-card server (MAIN +0x269000, linked at 0x80400000): functions whose C row is still linked at its
 * 0x8001xxxx placeholder row id, reached by the server's callers at the true address.  The readable alias in
 * config/names.tsv names the true address (the canonical name in the comment lowers to the placeholder), so the
 * calls keep their bytes.  Used by the server functions recovered in opus_nobody2 (docs/evidence/opus_nobody2.md).
 */
#include "common.h"
#include "frontend/card/service/selected_channel_data.h"

/* card_dev_drain_hw_events (row main/func_8001A4E4) at 0x804014E4 */
void invoke_callback_for_four_global_values(void);
/* card_dev_wait_poll_ready (row main/func_8001A3F8) at 0x804013F8 */
s32 wait_selected(s32 poll_id);
/* row main/func_8001AE2C at 0x80401E2C */
s32 process_slot_record_on_lookup_success(s32 slot_index);
/* row main/func_8001C25C at 0x8040325C */
void initialize_card_message_object_with_code_0xb(void *object);

/* server functions at their true addresses with no readable name there */
void func_80406F34(void *record_data);   /* card_dev_update_load_slot_highlight (row main/func_8001FF34) */
void func_804069FC(void *record_data);   /* row main/func_8001F9FC */
void func_804059A8(void *part);
void func_80407D38(void *part);
void func_80404570(void *part);

/* the card UI dirty word (0x8008DAB4) as the server's load-screen release reads and writes it: one scalar word
 * (its other users still declare their own array views locally) */
extern s32 card_ui_dirty_flags;

#endif
