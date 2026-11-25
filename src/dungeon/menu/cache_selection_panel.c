#include "engine/texture.h"
#include "engine/sprite.h"
#include "engine/menu.h"
#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_selection.h"
#include "engine/util.h"
#include "sdk/libgpu_types.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "slus/menu_count_template.h"
#include "slus.h"

/* Restore the base positions and colors for the two command rows. */
void style_selection_rows(CachedSelectionPanel *panel)
{
    s32 index;

    index = 0;
    do {
        panel->parts[index + 2]->position->x = 65;
        panel->parts[index + 2]->position->color.c.r = 0x68;
        panel->parts[index + 2]->position->color.c.g = 0x68;
        panel->parts[index + 2]->position->color.c.b = 0x60;
        panel->parts[index + 4]->position->x = 9;
        panel->parts[index + 6]->position->x = 121;
        panel->parts[index + 8]->position->x = 143;
        index++;
    } while (index < 2);
}

void animate_selection_rows(CachedSelectionPanel *panel)
{
    s32 previous_row;
    s32 cursor_offset;
    s32 index;
    s32 slide_offset;

    previous_row = panel->previous_row;
    cursor_offset = (panel->selected_row - previous_row) * (panel->progress << 4) / panel->duration + 10;
    panel->parts[1]->position->y = previous_row * 16 + cursor_offset;
    index = 0;
    do {
        u8 *level = (u8 *)panel + index + (panel->row_highlight - (u8 *)panel);
        s32 highlight = panel->row_highlight[index];
        s32 next;

        if (index == panel->selected_row) {
            next = highlight + (6 - highlight) / (panel->duration - panel->progress + 1);
        } else {
            next = highlight;
            if (next != 0) {
                next--;
            }
        }
        *level = next;

        slide_offset = (panel->row_highlight[index] * 8) / 6;
        panel->parts[index + 2]->position->x = slide_offset + 65;
        panel->parts[index + 8]->position->x = slide_offset + 143;
        panel->parts[index + 4]->position->x = slide_offset + 9;
        panel->parts[index + 6]->position->x = slide_offset + 121;
        panel->parts[index + 2]->position->color.c.r = panel->row_highlight[index] * 4 + 0x68;
        panel->parts[index + 2]->position->color.c.g = panel->row_highlight[index] * 4 + 0x68;
        panel->parts[index + 2]->position->color.c.b = panel->row_highlight[index] * 32 / 6 + 0x60;
        index++;
    } while (index < 2);
    if (panel->progress < panel->duration) {
        panel->progress++;
    }
}

/* Handle command input and update the animated selection. */
void process_selection_input(CachedSelectionPanel *panel)
{
    s32 pressed;
    s32 direction;

    if (g_game_work.buttons != 0 && panel->enabled != 0) {
        pressed = g_game_work.pressed_buttons;
        if (pressed & 0x20) {
            SD_Call(AUDIO_CANCEL);
            schedule_party_menu_close(panel->owner);
        } else if (pressed & 0x40) {
            SD_Call(AUDIO_ACCEPT);
            if (panel->selected_row != 0) {
                start_menu_message_mode(panel->owner);
                panel->enabled = 0;
            } else {
                schedule_menu_preview(panel->owner);
                NODE_HEADER(panel)->update_callback = slide_selection_panel_out;
                panel->enabled = 0;
            }
        } else if (g_game_work.buttons & 0x5000) {
            direction = 0;
            if (pressed & 0x4000) {
                direction = 1;
                panel->repeat_delay = 0;
                panel->duration = 3;
            } else if (pressed & 0x1000) {
                direction = -1;
                panel->repeat_delay = 0;
                panel->duration = 3;
            } else if (panel->repeat_delay >= 3) {
                s32 held;

                panel->repeat_delay--;
                held = g_game_work.buttons;
                if (held & 0x4000) {
                    direction = 1;
                    panel->duration = 2;
                } else if (held & 0x1000) {
                    direction = -1;
                    panel->duration = 2;
                }
            } else {
                panel->repeat_delay++;
            }
            if (direction != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                panel->progress = 0;
                panel->previous_row = panel->selected_row;
                panel->selected_row = advance_index_with_single_wrap(panel->selected_row, direction, 2);
            }
        }
    }
    animate_selection_rows(panel);
}

/* Handle steady-state command input and advance the selection. */
void update_selection_panel(CachedSelectionPanel *panel)
{
    process_selection_input(panel);
}

/* Slide toward the open position, then install the steady-state callback. */
void open_selection_panel(CachedSelectionPanel *panel)
{
    panel->links.display->x += (13 - panel->links.display->x) >> 2;
    if (panel->links.display->x < 16) {
        panel->links.display->x = 16;
        NODE_HEADER(panel)->update_callback = update_selection_panel;
    }
    process_selection_input(panel);
}

/* Slide the panel back toward its initial position. */
void slide_selection_panel_out(CachedSelectionPanel *panel)
{
    panel->links.display->x += (179 - panel->links.display->x) >> 2;
    if (panel->links.display->x >= 177) {
        NODE_HEADER(panel)->update_callback = update_selection_panel;
    }
    process_selection_input(panel);
}

/* Initialize the command labels, row packets and display templates. */
void populate_selection_parts(CachedSelectionPanel *panel)
{
    s32 index;

    panel->parts[0]->handler = get_menu_count_template(2);
    panel->parts[1]->handler = menu_leaf_template_6;

    for (index = 0; index < 2; index++) {
        panel->parts[index + 4]->handler = cached_selection_row_left_template;
        panel->parts[index + 6]->handler = cached_selection_row_middle_template;
        panel->parts[index + 2]->handler = panel->row_packets;
        panel->parts[index + 8]->handler = create_label_glyph_entries(cached_selection_row_indicator_texts[index], 1);
    }
}

/* Copy the shared display defaults and position the closed panel. */
void initialize_selection_display(CachedSelectionPanel *panel, ItemMenuDisplayLinks *links,
                                         StorageDisplayBlock *display, ItemMenuDisplayPosition *position)
{
    MenuDisplayBlock *display_defaults = &display_block_defaults;
    DisplayPositionWords *position_defaults = &display_vector_defaults;
    s32 *first_position_word = &position_defaults->unk0;

    display->words[0] = display_defaults->words[0];
    display->words[1] = display_defaults->words[1];
    display->words[2] = display_defaults->words[2];
    display->words[3] = display_defaults->words[3];
    position->words.unk0 = *first_position_word;
    position->words.unk4 = position_defaults->unk4;
    position->words.unk8 = position_defaults->unk8;

    links->display = &display->display;
    links->position = position;
    links->unk_00 = 0;
    links->display->x = 176;
    links->display->y = -88;
    links->display->depth = 0x200;
    links->display->mode = 4;
}

/* Lay out both rows and initialize the selection transition counters. */
void initialize_selection_positions(CachedSelectionPanel *panel)
{
    s32 index;

    panel->parts[0]->position->y = 18;
    for (index = 0; index < 2; index++) {
        panel->parts[index + 8]->position->x = 142;
        panel->parts[index + 8]->position->y = index * 16 + 130;
        panel->parts[index + 4]->position->x = 9;
        panel->parts[index + 4]->position->y = index * 16 + 10;
        panel->parts[index + 6]->position->x = 121;
        panel->parts[index + 6]->position->y = index * 16 + 10;
        panel->parts[index + 2]->position->x = 65;
        panel->parts[index + 2]->position->y = index * 16 + 10;
    }
    panel->duration = 1;
    panel->progress = 1;
    style_selection_rows(panel);
}

/* Bind the owner and prime the row graphics at the selected command. */
void prepare_selection_rows(CachedSelectionPanel *panel, ObjectNodeHeader *owner)
{
    panel->owner = owner;
    initialize_selection_panel_packets(panel->row_packets);
    panel->previous_row = panel->selected_row;
    populate_selection_parts(panel);
}

/* Prepare the rows, link the render blocks and lay out the command positions. */
void configure_selection_panel(CachedSelectionPanel *panel, ObjectNodeHeader *owner)
{
    prepare_selection_rows(panel, owner);
    initialize_selection_display(panel, &panel->links, &panel->display, &panel->position);
    initialize_selection_positions(panel);
}

/* Release both row indicator objects and clear their display slots. */
void release_selection_indicators(CachedSelectionPanel *panel)
{
    s32 index;

    for (index = 0; index < 2; index++) {
        flag_optional_object_for_removal(panel->parts[index + 8]->handler);
        panel->parts[index + 8]->handler = 0;
    }
}

/* Flag the panel for removal and release its draw resources. */
void release_selection_panel(CachedSelectionPanelNode *node)
{
    u16 flags;
    s32 global_flags;

    if (node != 0) {
        flags = node->header.flags | OBJECT_REMOVE_PENDING;
        global_flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        node->header.flags = flags;
        object_flag_block.flags = global_flags;
        release_selection_indicators(&node->panel);
        release_null_terminated_entries(node->panel.resources);
    }
}

/* Enable the panel when the command owner becomes active again. */
void enable_selection_panel(CachedSelectionPanelNode *node)
{
    if (node != 0) {
        node->panel.enabled = 1;
    }
}

/* Install the opening update on an existing panel. */
void schedule_selection_panel_open(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = open_selection_panel;
    }
}

/* The command panel uses a centered rectangle and ten linked display entries. */
const RECT cached_selection_panel_rectangle = {-56, -8, 112, 16};
const u8 cached_selection_panel_draw_order[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

ItemMenuPart *link_selection_panel_entries(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts,
                                                       (u8 *)cached_selection_panel_draw_order, 10);
}

/* Allocate the ten draw parts and their shared command storage. */
s32 prepare_selection_parts(CachedSelectionPanel *panel, s32 count)
{
    s32 ready = 0;
    u16 **resources = panel->resources;

    panel->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)resources, count, 8);
    if (panel->parts != 0) {
        panel->row_packets = (void *)(unsigned long)(u32)append_allocated_node_body((s32 *)resources, 8);
        if (panel->row_packets != 0) {
            panel->part_vector.unk0 = display_vector_defaults.unk0;
            panel->part_vector.unk4 = display_vector_defaults.unk4;
            panel->part_vector.unk8 = display_vector_defaults.unk8;
            set_menu_part_vectors(panel->parts, &panel->part_vector, 10);
            ready = 1;
        }
    }
    return ready;
}

CachedSelectionPanelNode *create_party_command_panel(ObjectNodeHeader *owner)
{
    CachedSelectionPanelNode *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedSelectionPanel *panel = &node->panel;

        if (prepare_selection_parts(panel, 10) != 0) {
            node->header.sprite = (SpriteFrameState *)&panel->links;
            panel->chain = link_selection_panel_entries(panel->parts);
            configure_selection_panel(panel, owner);
            NODE_HEADER(panel)->update_callback = open_selection_panel;
            register_node(&node->header, draw_tinted_node_sprites_scratch);
            enable_selection_panel(node);
            return node;
        }
        release_null_terminated_entries(panel->resources);
        node->header.flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

void initialize_selection_panel_packets(void *packets)
{
    init_packet_pair_and_gradient(packets, (void *)&cached_selection_panel_rectangle);
}
