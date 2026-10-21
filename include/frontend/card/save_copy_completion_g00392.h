#ifndef FRONTEND_CARD_SAVE_COPY_COMPLETION_G00392_H
#define FRONTEND_CARD_SAVE_COPY_COMPLETION_G00392_H
/* Save copy completion; G00392; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_80012358. */

#include "common.h"
#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard/interfaces.h"

typedef struct S_80025398_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_80025398_0;

/* arg0 in process_five_context_entries_or_fallback */
typedef struct S_80025398_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025398_1;

extern void card_boot_build_save_description(void *, s32);
extern void initialize_text_editor_context(void *, s32);
extern s32 card_boot_write_save_via_temporary_path(s32, s32);
extern s32 card_boot_load_save_and_clear_marker(s32, s32, s32);
extern void card_boot_show_copy_failure_notice(void *);
extern void card_boot_refresh_slot_window(s32);
extern void no_op_card_hook(s32);
extern u8 D_80024F7C[];

/* Functions defined in this translation unit. */
void initialize_save_description(void *owner, s32 value);
void process_five_context_entries_or_fallback(void *context);

#endif
