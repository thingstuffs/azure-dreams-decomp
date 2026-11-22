#ifndef FRONTEND_CARD_SAVE_COPY_COMPLETION_G00392_H
#define FRONTEND_CARD_SAVE_COPY_COMPLETION_G00392_H
/* Save copy completion; G00392; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_80012358. */

#include "common.h"

struct CardSaveImage;
#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"

#include "frontend/libcard/slot_menu.h"

void card_boot_build_save_description(struct CardSaveImage *save, s32 index);
void card_boot_store_save_icon_clut_and_frames(struct CardSaveImage *save, s32 record_index);
extern s32 card_boot_write_save_via_temporary_path(s32, struct CardSaveImage *);
extern s32 card_boot_load_save_and_clear_marker(s32, struct CardSaveImage *, s32);
extern void card_boot_show_copy_failure_notice(void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void card_boot_refresh_slot_window(struct ObjectNodeHeader *object);
extern void no_op_card_hook(s32);


/* Functions defined in this translation unit. */
void initialize_save_description(struct CardSaveImage *save, s32 value);
void write_save_and_refresh_slot_windows(struct CardSlotMenuState *context);

#endif
