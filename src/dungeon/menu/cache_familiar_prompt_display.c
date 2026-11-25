#include "engine/graphics.h"
#include "engine/menu/entry_words.h"
#include "engine/text.h"
#include "engine/util.h"
#include "engine/menu.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu/state.h"
#include "dungeon/menu_cache_stats.h"
#include "engine/item.h"
#include "shared/item_ids.h"
#include "slus.h"
#include "slus/card_selection_display_data.h"
#include "slus/data.h"
#include "slus/item_menu_primary_page_data.h"

static const CachedFamiliarCursorShape cached_familiar_cursor_shape = {
    0x80, 0x2a, -56, 9, 64, 64, 128, 0, {0, 0}, 112, 16
};

static const u8 cached_familiar_marker_parts[4] = {23, 24};

void initialize_familiar_cursor_shape(CachedFamiliarCursorShape *shape)
{
    *shape = cached_familiar_cursor_shape;
}

void set_familiar_previous_page(ItemMenuPart **parts, s32 show)
{
    ItemMenuPart *indicator = parts[19];

    if (show) {
        indicator->handler = item_menu_primary_page_data;
    } else {
        indicator->handler = 0;
    }
}

void set_familiar_next_page(ItemMenuPart **parts, s32 show)
{
    ItemMenuPart *indicator = parts[20];

    if (show) {
        indicator->handler = card_selection_display_data;
    } else {
        indicator->handler = 0;
    }
}

void position_familiar_prompt_cursors(ItemMenuPart **parts, s32 index)
{
    index %= 5;

    parts[2]->position->x = -56;
    parts[2]->position->y = index * 16 + 8;
    parts[3]->position->x = 0;
    parts[3]->position->y = index * 16 - 1;
}

void update_familiar_prompt_page(ItemMenuPart **parts, CachedFamiliarPrompt *prompt)
{
    set_familiar_previous_page(parts, prompt->current_page != 0);
    set_familiar_next_page(parts, prompt->current_page < prompt->last_page);
    position_familiar_prompt_cursors(parts, prompt->selected_actor_index);
    populate_familiar_page_labels(parts, prompt);
    refresh_familiar_slot_markers(parts, prompt);
}

void update_familiar_prompt_description(CachedFamiliarPrompt *prompt)
{
    if (prompt->actor_count != 0) {
        submit_script_with_registered_context((void *)monster_species_table[0][prompt->selected_actor->species].text_08);
    } else {
        build_object_registration_script(cached_familiar_empty_description);
    }
}

void run_familiar_prompt_input(CachedFamiliarPrompt *prompt)
{
    poll_familiar_prompt_input(prompt);
}

void advance_familiar_prompt_opening(CachedFamiliarPrompt *prompt)
{
    if (prompt->opening_step < 5) {
        s32 entry = select_display_spacing_table_entry(prompt->opening_step, 5);
        s32 width;

        prompt->parts[0]->handler = (void *)(unsigned long)(u32)read_display_spacing_word(entry);
        width = read_display_spacing_byte(entry);
        set_item_panel_height(prompt->packets, width == 16 ? 0 : width - 8);
        prompt->opening_step++;
    } else {
        prompt->draw_chain = link_cached_action_parts(prompt->parts);
        update_familiar_prompt_page(prompt->parts, prompt);
        update_familiar_prompt_description(prompt);
        NODE_HEADER(prompt)->update_callback = run_familiar_prompt_input;
    }
    poll_familiar_prompt_input(prompt);
}

static RECT cached_familiar_backdrop_rect = {-23, -8, 46, 16};

void build_familiar_backdrop(CachedFamiliarBackdrop *backdrop)
{
    fill_primitive_pair(backdrop->lines, (u8 *)&cached_familiar_backdrop_rect);
    build_tinted_gradient_rect(backdrop->gradient, (u8 *)&cached_familiar_backdrop_rect,
                                            (u8 *)&shared_primitive_color);
}

CachedFamiliarPromptNode *open_familiar_prompt(ObjectNodeHeader *owner, ActorRecord *actor,
                                                      s32 x, s32 y)
{
    return create_familiar_prompt(owner, actor, x, y);
}

void populate_familiar_page_labels(ItemMenuPart **parts, CachedFamiliarPrompt *prompt)
{
    s32 first = prompt->current_page * 5;
    s32 index;

    release_familiar_prompt_labels(parts);
    for (index = first; index < first + 5; index++) {
        s32 row;

        if (index >= prompt->actor_count) {
            break;
        }
        row = index - first;
        parts[row + 4]->handler = (void *)(unsigned long)(u32)lookup_item_category_mapped_value(ITEM_KIND_FAMILIAR,
                                                                    prompt->actors[index]->species);
        parts[row + 9]->handler = create_label_glyph_entries((char *)prompt->actors[index]->name, 0);
        parts[row + 14]->handler = prompt->actors[index]->hp == 0 ? prompt->packets->fainted_marker : 0;
    }
    for (; index < first + 5; index++) {
        s32 row = index - first;

        parts[row + 4]->handler = 0;
        parts[row + 9]->handler = 0;
        parts[row + 14]->handler = 0;
    }
}

void refresh_familiar_slot_markers(ItemMenuPart **parts, CachedFamiliarPrompt *prompt)
{
    const u8 *marker_parts;
    s32 index;
    s32 row;

    parts[23]->handler = 0;
    parts[24]->handler = 0;
    if (primary_actor_record->unk_AC.address == 0 && (prompt->available_slots & 1)) {
        parts[23]->position->x = 49;
        parts[23]->position->y = -1;
        parts[23]->handler = get_familiar_slot_marker(0);
    }
    if (primary_actor_record->unk_B0.address == 0 && (prompt->available_slots & 2)) {
        parts[24]->position->x = 25;
        parts[24]->position->y = -1;
        parts[24]->handler = get_familiar_slot_marker(1);
    }
    row = 0;
    index = prompt->current_page * 5;
    marker_parts = cached_familiar_marker_parts;
    for (; row < 5; row++, index++) {
        s32 slot;

        if (index >= prompt->actor_count) {
            break;
        }
        slot = get_menu_actor_index(prompt->actors[index]);
        if (slot != 2) {
            /* The indexed offset is the first operand of the address addition. */
            const u8 *marker_part = (const u8 *)(slot + (unsigned long)marker_parts);

            parts[*marker_part]->position->x = 48;
            parts[*marker_part]->position->y = (row % 5) * 16 + 22;
            parts[*marker_part]->handler = get_assigned_familiar_marker(slot);
        }
    }
}

void populate_familiar_prompt_parts(CachedFamiliarPrompt *prompt, ItemMenuPart **parts)
{
    ItemMenuPart *part;
    SpritePartTexture *frame;

    build_positioned_text_glyphs((u8 *)prompt->packets->fainted_marker, cached_familiar_fainted_text, 0);
    parts[0]->handler = 0;
    parts[1]->handler = prompt->packets;
    if (prompt->actor_count != 0) {
        s32 index;

        parts[2]->handler = cached_fixed_storage_cursor;
        parts[3]->handler = &prompt->packets->cursor;
        position_familiar_prompt_cursors(parts, 0);
        for (index = 4; index < 9; index++) {
            parts[index]->position->x = -48;
            parts[index]->position->y = (index - 4) * 16 + 21;
            parts[index]->handler = 0;
        }
        for (index = 9; index < 14; index++) {
            parts[index]->position->x = 96;
            parts[index]->position->y = (index - 9) * 16 + 136;
            parts[index]->handler = 0;
        }
        for (index = 14; index < 19; index++) {
            parts[index]->position->x = 88;
            parts[index]->position->y = (index - 14) * 16 + 136;
            parts[index]->handler = 0;
        }
        parts[19]->position->x = -64;
        parts[19]->position->y = 48;
        parts[19]->handler = 0;
        parts[20]->position->x = 64;
        parts[20]->position->y = 48;
        parts[20]->handler = 0;
    }
    parts[21]->position->x = 40;
    parts[21]->position->y = -16;
    if (prompt->available_slots & 1) {
        parts[21]->handler = cached_familiar_slot_one_button;
    }
    parts[22]->position->x = 16;
    parts[22]->position->y = -16;
    if (prompt->available_slots & 2) {
        parts[22]->handler = cached_familiar_slot_two_button;
    }
    move_familiar_prompt_selection(prompt, prompt->selected_actor_index);
    shade_familiar_assignment_slots(parts, prompt->assignment_slot);

    parts[25]->handler = menu_leaf_template_1;
    part = parts[25];
    frame = part->handler;
    part->position->x = -64 - frame->offset_x;
    part = parts[25];
    frame = part->handler;
    part->position->y = -24 - frame->offset_y;
    parts[26]->handler = &prompt->packets->backdrop;
    part = parts[26];
    frame = parts[25]->handler;
    part->position->x = -34 - frame->offset_x;
    parts[26]->position->y = -16;
}

CachedFamiliarPromptNode *create_familiar_prompt(ObjectNodeHeader *owner, ActorRecord *actor, s32 x, s32 y)
{
    CachedFamiliarPromptNode *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedFamiliarPrompt *prompt = &node->prompt;

        if (prepare_familiar_prompt(prompt, 27) != 0) {
            clear_win_sw0_resident_bit();
            node->header.sprite = (SpriteFrameState *)&prompt->links;
            prompt->draw_chain = link_familiar_prompt_parts(prompt->parts);
            setup_familiar_prompt(prompt, owner, actor, x, y);
            register_node(&node->header, draw_tinted_node_sprites_scratch);
            enable_familiar_prompt_input(node);
            return node;
        }
        release_null_terminated_entries(prompt->resources);
        node->header.flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}
