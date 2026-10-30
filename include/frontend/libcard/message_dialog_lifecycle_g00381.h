#ifndef FRONTEND_LIBCARD_MESSAGE_DIALOG_LIFECYCLE_G00381_H
#define FRONTEND_LIBCARD_MESSAGE_DIALOG_LIFECYCLE_G00381_H
/* Message dialog lifecycle; G00381; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000F934, CL:main/func_8000FAE8, CL:main/func_8000FB20, CL:main/func_8000FB48, CL:main/func_8000FBE8, CL:main/func_8000FC48, CL:main/func_8000FC90. */

#include "common.h"
#include "frontend/libcard.h"
#include "m2c_compat.h"
#include "records/Rec_func_8002290C_arg0.h"
#include "frontend/libcard/interfaces.h"

/* body in card_boot_create_or_reset_message_dialog */
#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef struct S_80022CD8_0_pre {
    void ** unk_00;
    u8 pad_04[0xC];
} S_80022CD8_0_pre;

/* the 0x10 bytes before arg0 in card_boot_activate_message_dialog, addressed as arg0[-1] */
typedef struct S_80022CD8_0 {
    s32 unk_00;
    u8 pad_04[0x4];
    s32 unk_08;
    s32 unk_0C;
} S_80022CD8_0;

typedef struct S_set_handler_0 {
    u8 pad_00[0x10];
    void * unk_10;
} S_set_handler_0;

/* out in set_handler */
typedef struct S_80022D60_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80022D60_0;

/* context in card_boot_create_or_reset_message_dialog */
typedef struct S_80022D60_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80022D60_1;

/* base in card_boot_create_or_reset_message_dialog */
typedef struct S_80022D60_2 {
    u8 pad_00[0x8C8];
    struct S_800491F4 *unk_8C8;
} S_80022D60_2;

extern void card_boot_initialize_message_render_templates(s32 entity, s32 primary_data, s32 secondary_data);
extern void card_boot_initialize_dialog_packets_and_display(s32 record);
/* arg0 in card_boot_activate_message_dialog */
extern void *card_boot_build_message_window_packets(void *buffer, void *layout);
extern void card_boot_update_message_choice_highlight(void *object);
extern u8 D_80022524[];
extern u8 D_800226A8[];
extern struct S_800491F4 *card_boot_link_message_display_entries(void *ptr);
extern void card_boot_initialize_dialog_draw_nodes(void *context, s32 value);
extern s32 card_boot_close_message_dialog(s32 flagLinkedRecord);
extern void *initialize_scene_object_in_buffer(s32 value0, void *ptr, s32 value2);
extern void register_node(void *base, void *handler);
extern s32 find_active_list_node(void *base);
extern void bzero(void *ptr, s32 size);
extern u8 D_80022CD8[];
extern u8 menu_backdrop_tag[];
extern u8 D_800287E8[];

/* Functions defined in this translation unit. */
void card_boot_measure_five_line_message(CardMenuEntry *entry);
void card_boot_bind_message_dialog_record(Rec_func_8002290C_arg0 *record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
void card_boot_initialize_message_dialog_layout(s32 record, s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);
void card_boot_activate_message_dialog(void *object);
u8 *card_boot_create_or_reset_message_dialog(s32 value_14, s32 entry_index, s32 value_0c, s32 value_20);

#endif
