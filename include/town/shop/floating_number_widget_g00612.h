#ifndef TOWN_SHOP_FLOATING_NUMBER_WIDGET_G00612_H
#define TOWN_SHOP_FLOATING_NUMBER_WIDGET_G00612_H

struct ObjectNodeHeader;
/* Floating number widget declarations (G00612). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B41D8, CL:town/func_800B4200, CL:town/func_800B4298, CL:town/func_800B43B0, CL:town/func_800B4410. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct S_800B19F8_1 {
    u8 pad_00[0x48];
    void * unk_48;
    void * unk_4C;
    void * unk_50;
    void * unk_54;
} S_800B19F8_1;

/* arg0 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_2 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_2;

/* ((S_800B19F8_1 *)arg0)->unk_48 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_3 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_3;

/* ((S_800B19F8_1 *)arg0)->unk_4C in initialize_panel_content_and_positions */
typedef struct S_800B19F8_4 {
    s32 unk_00;
    void * unk_04;
} S_800B19F8_4;

/* ((S_800B19F8_1 *)arg0)->unk_54 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B19F8_5;

/* ((S_800B19F8_1 *)arg0)->unk_50 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_6;

/* ((S_800B19F8_2 *)(((S_800B19F8_1 *)arg0)->unk_48))->unk_04 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_7;

/* ((S_800B19F8_3 *)(((S_800B19F8_1 *)arg0)->unk_4C))->unk_04 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_8 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_8;

/* ((S_800B19F8_4 *)(((S_800B19F8_1 *)arg0)->unk_54))->unk_04 in initialize_panel_content_and_positions */
typedef struct S_800B19F8_9 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B19F8_9;

typedef struct S_800B19F8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_800B19F8_0;

typedef struct S_800B1B04_0 {
    s32 unk_00;
    s32 unk_04;
} S_800B1B04_0;

typedef struct Node { s32 unk0; void *data; void *anchor; s32 unkC; } Node;

typedef struct S_800B1BEC_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0x34];
    void * unk_44;
} S_800B1BEC_0;

/* part in create_dual_buffer_object */

/* ((S_800B19F8_5 *)(((S_800B19F8_1 *)arg0)->unk_50))->unk_04 in initialize_panel_content_and_positions */
extern void *decode_fullwidth_text(void *a0, u8 *a1, s32 a2);
extern void refresh_formatted_global_display(void *a0);
extern void func_800B18F8(s32 a0);
extern s32 D_80078D6C[4];
extern u8 D_800D1560[16];
void initialize_templated_state_and_position(s32, s32, s32, s32, s32);
extern s32 display_block_defaults[4];
/* object in create_dual_buffer_object */
extern void *create_callback_pair_default(s32);
extern void flag_object_for_removal(void *);
extern void *process_context_with_selector_4(void *);
extern void register_node(void *, void *);
extern void lower_value_toward_target(struct ObjectNodeHeader *object);
extern u8 dungeon_menu_tag[];

/* Functions defined in this translation unit. */
void initialize_panel_content_and_positions(S_800B19F8_0 *panel);
void store_pair_values(S_800B1B04_0 *pair, s32 first, s32 second);
void build_owned_floating_number_widget(s32 object_addr, s32 setup_value, s32 update_value_1, s32 update_value_2);
void initialize_four_anchored_nodes(void *state);
void *create_dual_buffer_object(s32 setup_value, s32 x, s32 y);

#endif
