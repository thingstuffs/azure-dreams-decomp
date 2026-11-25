#include "town/shop/state.h"
#include "town/shop/monster_status_idle.h"
#include "town/shop/monster_status_initialization_g00634.h"
#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_stats.h"
#include "engine/resource.h"
#include "slus.h"

const u8 menu_opening_icon_order[4] = {5, 3};

SpritePartCommand *cached_opening_status_template_by_type[4] = {
    &cached_opening_status_templates[0],
    &cached_opening_status_templates[1],
    &cached_opening_status_templates[2],
    &cached_opening_status_templates[3],
};

/* Append the secondary menu entries and return the first link. */
ItemMenuPart *join_status_display_entries(ItemMenuPart **entries, ShopFirstCallbackObject *state)
{
    ItemMenuPart *head;

    head = link_cached_monster_display_entries(entries);
    append_linked_chain((struct Struct_C_next *)head,
                        (struct Struct_C_next *)link_menu_entries(entries));
    return head;
}

/* Choose the actor display layout using the slot index. */
void build_status_display(ShopFirstCallbackObject *state)
{
    if (state->slot_index != 0) {
        initialize_party_display(state->actor, state->parts, state->texture);
    } else {
        initialize_actor_status_display(state->actor, state->parts, state->texture);
    }
}

/* Clear the two upper slots and reset the lower panel height. */
void reset_status_parts(ShopFirstCallbackObject *state)
{
    ItemMenuPart *part;
    s32 slot;

    slot = 21;
    do {
        part = state->parts[slot];
        slot += 1;
        part->handler = 0;
    } while (slot < 23);
    state->parts[24]->handler = state->pad_18;
    set_monster_status_panel_height(state->parts[24]->handler, 0);
}

/* Lay out both icons during the five-step opening sequence. */
void layout_cached_opening_icons(ItemMenuPart **parts, s32 display_mode) {
    s32 mode;
    s32 total_width;
    s32 entry_index;
    const u8 *lookup;
    ItemMenuPart **entry_slot;
    s32 x_offset;
    s32 spacing;
    s32 entry_id;
    ItemMenuPart *entry;
    ItemMenuPartPosition *position;

    entry_index = (total_width = 0);
    lookup = menu_opening_icon_order;
    entry_slot = parts;
    do {
        mode = display_mode;
        entry = entry_slot[21];
        /* The indexed offset is the first operand of the address addition. */
        entry_id = select_display_spacing_table_entry(mode, *(const u8 *)(entry_index + (unsigned long)lookup));
        if ((entry_index == 0) && (mode == 4)) {
            entry_id -= 1;
        }
        entry->handler = (void *)(unsigned long)(u32)read_display_spacing_word(entry_id);
        spacing = read_display_spacing_byte(entry_id);
        if (spacing == 0x10) {
            entry->position->y = 0;
        } else {
            x_offset = total_width - (entry_index * 8);
            position = entry->position;
            total_width += spacing;
            position->y = x_offset;
        }
        entry_index += 1;
        entry_slot++;
    } while (entry_index < 2);
    spacing = 0;
    if (total_width != 0) {
        spacing = total_width - 0x14;
    }
    set_monster_status_panel_height(parts[24]->handler, spacing);
}

/* Finish opening the status panel and leave its display chain idle. */
void advance_status_opening(ShopFirstCallbackObject *state)
{
    s16 step = state->opening_step;

    if (step < 5) {
        layout_cached_opening_icons(state->parts, step);
        state->opening_step = state->opening_step + 1;
        return;
    }
    state->display.next = join_status_display_entries(state->parts, state);
    build_status_display(state);
    state->first_callback = noop_monster_status_idle;
}

/* Release and reset the text handles in the 25-entry display list. */
void release_status_entries(ItemMenuPart **entries) {
    s32 entry_index;
    u8 entry_type;
    ItemMenuPart *entry;
    ItemMenuPartPosition *position;

    for (entry_index = 0; entry_index < 25; entry_index++) {
        entry = entries[entry_index];
        position = entry->position;
        entry_type = position->type;
        if (entry_type == 2) {
            flag_optional_object_for_removal(entry->handler);
            entries[entry_index]->handler = 0;
            position = entries[entry_index]->position;
            position->type = 0;
        } else if (entry_type == 1) {
            flag_object_for_removal(entry->handler);
            entries[entry_index]->handler = 0;
            position = entries[entry_index]->position;
            position->type = 0;
        }
    }
}

void initialize_status_state(ShopFirstCallbackObject *state, ActorRecord *actor, s32 slot_index)
{
    state->slot_index = slot_index;
    state->actor = actor;
    state->unk_0C = 0;
    state->opening_step = 0;
    state->first_callback = advance_status_opening;
    state->texture = get_monster_status_type_data(state->slot_index);
    queue_monster_status_reload(state);
}

void change_status_display_target(MenuEntryObject *object, ActorRecord *actor, s16 slot_index)
{
    if (object != 0) {
        ShopFirstCallbackObject *state = &object->state;

        release_status_entries(state->parts);
        state->slot_index = slot_index;
        state->actor = actor;
        build_status_display(state);
        queue_monster_status_reload(state);
    }
}
