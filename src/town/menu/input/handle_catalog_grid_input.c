#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef struct {
    void *field_0;
    s16 field_4;
    s16 field_6;
    u8 pad8[2];
    u8 field_A;
    u8 field_B;
    u8 padC[3];
    u8 field_F;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u8 pad14;
    u8 field_15;
    u8 field_16;
    u8 field_17[2];
    u8 pad19[0x43];
} Object;

extern u8 D_80082E6B;
extern s8 D_80080A84;
extern s8 D_80129728;

extern u8 is_catalog_entry_available(u8);
extern void SD_Call(s32);
extern void select_paired_value_tables(Object *);
extern void create_deferred_resource_transition_task(s32, s32, s32, s32);
extern void release_null_terminated_entries(void *);
extern void remove_scene_runtime_callback(void);

/* Handles input to update object selections, action states, and exit behavior. */
void handle_catalog_grid_input(Object *object)
{
    GameWork *input_state = &g_game_work;
    u32 input_flags;
    u32 side_value;
    u8 active_value;
    u8 alternate_value;
    u8 target_value;
    s32 entry_index;
    s32 **reset_entries;

    input_flags = ((u32)input_state->pressed_buttons);
    if (input_flags & 0x40) {
        s32 slot_index;

        if (!is_catalog_entry_available(object->field_13)) {
            return;
        }
        SD_Call(0x702);
        slot_index = object->field_16;
        target_value = object->field_13;
        active_value = *((u8 *)object + slot_index + 0x17);
        if (active_value == target_value) {
            object->field_A = 6;
            object->field_4 = 1;
            object->field_6 = 0x19;
            return;
        }
        slot_index ^= 1;
        alternate_value = *((u8 *)object + slot_index + 0x17);
        if (alternate_value == target_value) {
            object->field_16 = slot_index;
            select_paired_value_tables(object);
            object->field_A = 6;
            object->field_4 = 1;
            object->field_6 = 0x19;
            return;
        }
        if (active_value != 0xFF && alternate_value == 0xFF) {
            object->field_16 = slot_index;
            select_paired_value_tables(object);
            object->field_A = 5;
            object->field_B = 0;
            return;
        }
        object->field_A = 5;
        object->field_B = 0;
        return;
    }

    if (input_flags & 0x20) {
        SD_Call(0x700);
        if (D_80082E6B == 0x17) {
            create_deferred_resource_transition_task(0, 0, 0, 0);
            reset_entries = (s32 **)&D_80129728;
            for (entry_index = 0; entry_index < 98; entry_index++) {
                *reset_entries[entry_index] = 0;
            }
            *(u16 *)((u8 *)object->field_0 + 0x1E) |= 0x2000;
            release_null_terminated_entries((u8 *)object + 0x5C);
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            object_flag_block.flags |= 0x8000;
            remove_scene_runtime_callback();
            D_80080A84 = 2;
            return;
        }
    }

    input_flags = ((u32)input_state->pressed_buttons);
    if (input_flags & 0x8000) {
        u8 selection_group;
        s32 group;

        if (object->field_10 == 0) {
            object->field_F += 3;
            group = object->field_F;
            object->field_F = group & 3;
        }
        selection_group = object->field_F;
        object->field_10 ^= 1;
        if ((selection_group == 3) && (object->field_15 != 0)) {
            object->field_F = 2;
        }
        object->field_A = 0;
        return;
    }
    if (input_flags & 0x2000) {
        u8 selection_group;
        s32 group;

        if (object->field_10 != 0) {
            object->field_F += 1;
            group = object->field_F;
            object->field_F = group & 3;
        }
        selection_group = object->field_F;
        object->field_10 ^= 1;
        if ((selection_group == 3) && (object->field_15 != 0)) {
            object->field_F = 0;
        }
        object->field_A = 0;
        return;
    }

    input_flags = ((u32)input_state->buttons);
    if (input_flags & 0x1000) {
        if (object->field_F != 3) {
            u32 selection_value;
            s32 previous_selection;
            s32 masked;

            selection_value = 1;
            (*(s16 *)&object->field_4) = selection_value;
            selection_value = object->field_11;
            previous_selection = selection_value;
            selection_value += 7;
            object->field_11 = selection_value;
            object->field_6 = 4;
            masked = object->field_11;
            object->field_11 = masked & 7;
            object->field_12 = previous_selection;
            if ((*(u8 *)&object->field_11) != 7) {
                object->field_A = 2;
                return;
            }
            side_value = object->field_10;
            object->field_A = 3;
            object->field_10 = side_value ^ 1;
            return;
        }
    } else {
        if (!(input_flags & 0x4000)) {
            return;
        }
        input_flags = 1;
        if (object->field_F != 3) {
            u32 selection_value;
            s32 previous_selection;
            s32 masked;

            selection_value = object->field_11;
            previous_selection = selection_value;
            selection_value += 1;
            object->field_11 = selection_value;
            object->field_4 = input_flags;
            masked = object->field_11;
            object->field_11 = masked & 7;
            object->field_12 = previous_selection;
            object->field_6 = 4;
            if ((*(u8 *)&object->field_11) == 0) {
                side_value = object->field_10;
                object->field_A = 3;
                object->field_10 = side_value ^ 1;
                return;
            }
            object->field_A = 2;
            return;
        }
    }
    side_value = 1;
    object->field_4 = side_value;
    object->field_6 = 4;
    object->field_A = 4;
    object->field_10 = object->field_10 ^ 1;
}
