#include "engine/window.h"
#include "shared/object_node_flags.h"
#include "shared/object_node.h"
#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "dungeon/menu/state.h"

extern void set_item_data_from_lookup();

extern void advance_paired_object_sequence();
extern s32 inventory_allocate_and_initialize_child(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 allocate_initialized_child_object();
extern s32 create_menu_child_object();
extern s32 item_panel_display_ids;

typedef struct S_80025198_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_0;

typedef struct S_80025198_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    u8 pad_08[0x8];
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
    void *unk_2C;
    void *unk_30;
    void *unk_34;
} S_80025198_1;

typedef struct S_80025198_2 {
    u8 unk_00;
    u8 unk_01;
} S_80025198_2;

typedef struct S_80025198_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_80025198_3;

typedef struct S_80025198_4 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_80025198_4;

typedef struct S_80025198_5 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_80025198_5;

/* Allocate and initialize an object, cleaning up if any required resource is missing. */
void *allocate_item_object(s32 value_00, s32 value_10, s32 value_18, void *descriptor, s32 setup_arg) {
    s32 *display_ids;
    s32 resource_index;
    S_80025198_2 *descriptor_data;
    S_80025198_1 *state;
    s32 *globals_base;
    ObjectNodeHeader *object;
    void *resource_cursor;

    object = allocate_flagged_object_node(0);
    if (object != NULL) {
        descriptor_data = descriptor;
        state = ((void *)object) + 0x20;
        ((S_80025198_0 *)object)->unk_20 = value_00;
        state->unk_10 = value_10;
        state->unk_14 = (s32) descriptor_data->unk_01;
        state->unk_18 = value_18;
        state->unk_1C = (s32) descriptor_data->unk_00;
        set_item_data_from_lookup(state, descriptor_data, setup_arg);
        (object->update_callback) = 0;
        if (runtime_dispatch_state.mode != 1) {
            clear_state_flag_bit();
        }
        display_ids = &item_panel_display_ids;
        state->unk_2C = window_create_animated_content_panel(8, 0xEC, 0x64, 0xEC, 0x64, 0x50, 1, item_panel_display_ids);
        state->unk_30 = window_create_animated_content_panel(4, 0xEC, 0x64, 0xEC, 0x74, 0x50, 1,
            ((S_80025198_3 *)display_ids)->unk_04);
        state->unk_34 = window_create_animated_content_panel(0x10, 0xEC, 0x64, 0xEC, 0x84, 0x50, 1,
            ((S_80025198_3 *)display_ids)->unk_08);
        state->unk_20 = inventory_allocate_and_initialize_child(object, state->unk_14,
            state->unk_04);
        state->unk_24 = create_menu_child_object(object, state->unk_14);
        state->unk_28 = allocate_initialized_child_object(object, state->unk_14,
            state->unk_04);
        globals_base = (s32 *) 0x80080000;
        for (resource_index = 0, resource_cursor = state; resource_index < 3; resource_index++, resource_cursor += 4) {
            if (((S_80025198_4 *)resource_cursor)->unk_20 == 0) {
                advance_paired_object_sequence(state);
                ((ObjectNodeHeader *)((u8 *)state - 0x20))->flags = (u16) (((ObjectNodeHeader *)((u8 *)state - 0x20))->flags | NODE_REMOVE);
                object = NULL;
                ((S_80025198_5 *)globals_base)->unk_14A0 |= 0x8000;
                break;
            }
        }
    }
    return object;
}
