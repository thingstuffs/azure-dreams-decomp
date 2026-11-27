#include "common.h"
#include "shared/runtime_dispatch.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "engine/scene.h"
#include "town/menu.h"
#include "town/menu/catalog.h"
#include "town/menu/catalog_parts.h"
#include "engine/item.h"
#include "town/scene.h"
#include "slus.h"
#include "slus/animation_tick_data.h"

typedef struct {
    void *field_0;
    s16 anim_step;
    s16 anim_duration;
    u8 pad8[2];
    u8 phase;
    u8 load_phase;
    u8 padC[3];
    u8 page;
    u8 side;
    u8 column;
    u8 prev_column;
    u8 entry_id;
    u8 pad14;
    u8 skip_last_page;
    u8 active_slot;
    u8 choices[2];
    u8 pad19[0x43];
} Object;


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

        if (!is_catalog_entry_available(object->entry_id)) {
            return;
        }
        SD_Call(0x702);
        slot_index = object->active_slot;
        target_value = object->entry_id;
        active_value = object->choices[slot_index];
        if (active_value == target_value) {
            object->phase = 6;
            object->anim_step = 1;
            object->anim_duration = 0x19;
            return;
        }
        slot_index ^= 1;
        alternate_value = object->choices[slot_index];
        if (alternate_value == target_value) {
            object->active_slot = slot_index;
            select_paired_value_tables((CatalogDisplay *)object);
            object->phase = 6;
            object->anim_step = 1;
            object->anim_duration = 0x19;
            return;
        }
        if (active_value != 0xFF && alternate_value == 0xFF) {
            object->active_slot = slot_index;
            select_paired_value_tables((CatalogDisplay *)object);
            object->phase = 5;
            object->load_phase = 0;
            return;
        }
        object->phase = 5;
        object->load_phase = 0;
        return;
    }

    if (input_flags & 0x20) {
        SD_Call(0x700);
        if (scene_mode_code == 0x17) {
            create_deferred_resource_transition_task(0, 0, 0, 0);
            reset_entries = (s32 **)catalog_display_node_slots;
            for (entry_index = 0; entry_index < 98; entry_index++) {
                *reset_entries[entry_index] = 0;
            }
            *(u16 *)((u8 *)object->field_0 + 0x1E) |= 0x2000;
            release_null_terminated_entries((u8 *)object + 0x5C);
            NODE_HEADER(object)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            remove_scene_runtime_callback();
            animation_tick_scale = 2;
            return;
        }
    }

    input_flags = ((u32)input_state->pressed_buttons);
    if (input_flags & 0x8000) {
        u8 selection_group;
        s32 group;

        if (object->side == 0) {
            object->page += 3;
            group = object->page;
            object->page = group & 3;
        }
        selection_group = object->page;
        object->side ^= 1;
        if ((selection_group == 3) && (object->skip_last_page != 0)) {
            object->page = 2;
        }
        object->phase = 0;
        return;
    }
    if (input_flags & 0x2000) {
        u8 selection_group;
        s32 group;

        if (object->side != 0) {
            object->page += 1;
            group = object->page;
            object->page = group & 3;
        }
        selection_group = object->page;
        object->side ^= 1;
        if ((selection_group == 3) && (object->skip_last_page != 0)) {
            object->page = 0;
        }
        object->phase = 0;
        return;
    }

    input_flags = ((u32)input_state->buttons);
    if (input_flags & 0x1000) {
        if (object->page != 3) {
            u32 selection_value;
            s32 previous_selection;
            s32 masked;

            selection_value = 1;
            (*&object->anim_step) = selection_value;
            selection_value = object->column;
            previous_selection = selection_value;
            selection_value += 7;
            object->column = selection_value;
            object->anim_duration = 4;
            masked = object->column;
            object->column = masked & 7;
            object->prev_column = previous_selection;
            if ((*&object->column) != 7) {
                object->phase = 2;
                return;
            }
            side_value = object->side;
            object->phase = 3;
            object->side = side_value ^ 1;
            return;
        }
    } else {
        if (!(input_flags & 0x4000)) {
            return;
        }
        input_flags = 1;
        if (object->page != 3) {
            u32 selection_value;
            s32 previous_selection;
            s32 masked;

            selection_value = object->column;
            previous_selection = selection_value;
            selection_value += 1;
            object->column = selection_value;
            object->anim_step = input_flags;
            masked = object->column;
            object->column = masked & 7;
            object->prev_column = previous_selection;
            object->anim_duration = 4;
            if ((*&object->column) == 0) {
                side_value = object->side;
                object->phase = 3;
                object->side = side_value ^ 1;
                return;
            }
            object->phase = 2;
            return;
        }
    }
    side_value = 1;
    object->anim_step = side_value;
    object->anim_duration = 4;
    object->phase = 4;
    object->side = object->side ^ 1;
}
