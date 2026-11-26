#include "frontend/card.h"
#include "dungeon/menu_cache_paged.h"
#include "dungeon/menu_cache.h"
#include "dungeon/player.h"
#include "shared/record_ptrs.h"
#include "engine/text.h"
#include "engine/sprite.h"
#include "engine/graphics.h"
#include "dungeon/menu_cache_actor_choice.h"
#include "engine/effect.h"
#include "engine/item.h"
#include "engine/menu.h"
#include "dungeon/menu_cache_close.h"
#include "dungeon/menu/state.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/item.h"
#include "dungeon/menu_cache_linked_actor.h"
#include "dungeon/menu_cache_party_menu.h"
#include "dungeon/menu_cache_selection.h"
#include "engine/util.h"
#include "sdk/libgpu_types.h"
#include "engine/node/allocation.h"
#include "engine/runtime.h"
#include "shared/audio_commands.h"
#include "slus/resource_transition_task.h"
#include "shared/game_work.h"
#include "engine/texture.h"
#include "slus.h"

/* Fade both linked actor entries using the two selection states. */
const u8 cached_actor_shade_keys[2][2] = {{0, 1}, {1, 0}};
const SpriteColor cached_actor_shade_colors[2] = {{0x00808080}, {0x00282828}};

void shade_actor_choices(CachedActorChoice *choice)
{
    s32 index;

    for (index = 0; index < choice->actor_count; index++) {
        AnimatedSelectionEntry *entry = choice->entries[index];
        const u8 *row = cached_actor_shade_keys[index];
        s32 start = cached_actor_shade_colors[row[choice->previous_index]].c.r;
        s32 end = cached_actor_shade_colors[row[choice->selected_index]].c.r;
        s32 delta = (end - start) * choice->transition_tick / choice->transition_frames;
        MenuDisplayNode *node = entry->display;

        node->block->color.r = start + delta;
        node->block->color.g = node->block->color.r;
        node->block->color.b = node->block->color.r;
    }
}


/* Fill the selector from the active links on the primary actor. */
void initialize_actor_choice(CachedActorChoice *choice)
{
    fill_cached_choice_actors(choice->actors, &choice->actor_count);
}

/* Find the chosen actor in the selector list. */
/* Use the concrete body type so each selector keeps its original field offsets. */
s32 find_actor_choice(CachedActorChoice *choice, s32 actor_index)
{
    void *actor = get_menu_actor(actor_index);
    s32 actor_count = choice->actor_count;
    s32 index;

    for (index = 0; index < actor_count; index++) {
        if (choice->actors[index] == actor) {
            return index;
        }
    }
    return index;
}


/* Open and advance the selectors using their own callback bindings. */
void advance_actor_choice_transition(CachedActorChoice *choice)
{
    reorder_actor_choices(choice);
    if (choice->transition_tick++ >= choice->transition_frames) {
        choice->animate = idle_actor_choice;
    }
}

void spread_actor_choices(CachedActorChoice *choice)
{
    s32 index;

    if (choice->spacing >= 33) {
        choice->spacing = 32;
        choice->animate = idle_actor_choice;
    }
    for (index = 0; index < choice->actor_count; index++) {
        MenuDisplayNode *node = choice->entries[index]->display;
        node->block->fields.x = choice->spacing * index - 92;
    }
    choice->spacing += (40 - choice->spacing) >> 3;
}


/* Reset the transition, wrap the selected index and refresh the preview. */
void begin_actor_choice_change(CachedActorChoice *choice, s32 delta)
{
    choice->transition_tick = 0;
    if (choice->animate == spread_actor_choices) {
        choice->spacing = 32;
        spread_actor_choices(choice);
    }
    choice->animate = advance_actor_choice_transition;
    choice->previous_index = choice->selected_index;
    choice->selected_index = advance_index_with_single_wrap(choice->selected_index, delta, choice->actor_count);
    if (choice->choice_mode == 0) {
        s32 actor_index = get_menu_actor_index(choice->actors[choice->selected_index]);
        set_cached_actor_preview_target(choice->owner, actor_index);
    }
}

/* Process the direction keys, repeat delay and direct actor shortcuts. */
void poll_actor_choice_input(CachedActorChoice *choice)
{
    GameWork *input;
    s32 delta;

    input = &g_game_work;
    delta = 0;
    if (input->buttons != 0 && choice->actor_count >= 2) {
        READ_CACHED_CHOICE_DIRECTION(choice, input, delta);
        if (delta != 0) {
            SD_Call(0x504);
            begin_actor_choice_change(choice, delta);
        }
    }
}

/* Apply the installed animation before reading selection input. */
void update_actor_choice(CachedActorChoice *choice)
{
    choice->animate(choice);
    poll_actor_choice_input(choice);
}

s32 initialize_actor_choice_entries(CachedActorChoice *choice)
{
    s32 index = 0;
    const u8 (*keys)[2] = cached_actor_shade_keys;

    do {
        ActorRecord *actor = choice->actors[index];

        if (actor != 0) {
            s32 key = keys[choice->selected_index][index];
            s32 offset_y = key * 12 - 92;

            choice->entries[index] = (AnimatedSelectionEntry *)allocate_menu_entry_object(choice->actors[index], index + 1,
                choice->spacing * index - 92, choice->origin_y + offset_y, 512 + key * 30);
            if (choice->entries[index] == 0) {
                return 0;
            }
        }
        index++;
    } while (index < 2);
    choice->transition_tick = 1;
    choice->transition_frames = 1;
    reorder_actor_choices(choice);
    return 1;
}

ObjectNodeHeader *create_actor_choice(ObjectNodeHeader *owner, s32 actor_index, s32 mode,
                                             s32 origin_y, s32 directional_enabled)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);
    if (node != 0) {
        CachedActorChoice *choice = NODE_BODY(node);

        initialize_actor_choice(choice);
        choice->selected_index = find_actor_choice(choice, actor_index);
        choice->owner = owner;
        choice->choice_mode = mode;
        choice->origin_y = origin_y;
        choice->directional_enabled = directional_enabled;
        node->update_callback = update_actor_choice;
        choice->animate = spread_actor_choices;
        if (initialize_actor_choice_entries(choice) == 0) {
            release_actor_choice(node);
            node = 0;
        }
    }
    return node;
}

ObjectNodeHeader *create_cached_linked_actor_selector(ObjectNodeHeader *owner, s32 actor_index)
{
    return create_actor_choice(owner, actor_index, 0, 0, 1);
}

ObjectNodeHeader *create_fusion_actor_selector(ObjectNodeHeader *owner, s32 actor_index, s32 origin_y)
{
    return create_actor_choice(owner, actor_index, 1, origin_y, 1);
}

void poll_cached_actor_message_cancel(CachedActorMessage *message)
{
    GameWork *input = &g_game_work;

    if (input->buttons != 0 && (input->pressed_buttons & 0x20)) {
        SD_Call(AUDIO_CANCEL);
        NODE_HEADER(message)->update_callback = mark_node_for_removal;
        enqueue_script_message_command();
    }
}

void start_cached_actor_message_transition(CachedActorMessage *message)
{
    if (create_resource_transition_task(NODE_HEADER(message)) != 0) {
        NODE_HEADER(message)->update_callback = refresh_vram_blocks_on_flag;
        enqueue_script_message_command();
    }
}

void poll_cached_actor_message_switch(CachedActorMessage *message)
{
    s32 state = poll_window_switch_flags();

    if (state != 0) {
        void *next;

        if (state == 1) {
            next = start_cached_actor_message_transition;
        } else {
            next = mark_node_for_removal;
        }
        NODE_HEADER(message)->update_callback = next;
        enqueue_script_message_command();
    } else {
        poll_cached_actor_message_cancel(message);
    }
}

ObjectNodeHeader *create_cached_actor_message(ObjectNodeHeader *owner)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedActorMessage *message = NODE_BODY(node);

        message->owner = owner;
        set_message_mode(0);
        call_message_mode_handler();
        dispatch_control_string_with_suffix(cached_actor_message_text);
        node->update_callback = poll_cached_actor_message_switch;
    }
    return node;
}

void style_familiar_behavior_row(ItemMenuPart *part, ItemMenuPart *label, s32 index, s32 highlight)
{
    s32 row_saturation = (index << 7) - index;
    s32 base_saturation;
    s32 shade = 8 - highlight;
    s32 dim;
    s32 fade;
    s32 saturation_loss;
    ItemMenuPartPosition *position;
    s32 saturation;
    s16 value;
    CachedMenuPartTransform *transform = (CachedMenuPartTransform *)part->vector;

    base_saturation = row_saturation / 5 + 128;
    transform->rotation_y = -(shade << 8);
    saturation_loss = base_saturation * shade;
    fade = shade * 5;
    dim = -128 - fade * 2;
    position = part->position;
    position->color.c.b = dim;
    position->color.c.g = dim;
    position->color.c.r = dim;
    saturation = (s16)(base_saturation - saturation_loss / 8);
    value = 255 - fade * 4;
    convert_hsv_to_rgb(128, saturation, value, &label->position->color.c.r);
}

void confirm_familiar_behavior(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedFamiliarBehaviorPanel *panel = NODE_BODY(node);
        s16 actor_index = get_menu_actor_index(panel->actor);
        s32 mode = 4 - panel->selected_mode;
        s16 command_mode = mode;

        set_linked_actor_code_and_mirror(actor_index, command_mode);
        append_packed_action_record(dungeon_actor_ring_anchor, 120, actor_index, command_mode);
    }
}

void advance_familiar_behavior_opening(CachedFamiliarBehaviorPanel *panel)
{
    ItemMenuDisplayBlock *display = panel->links.display;

    display->ramp += (0x1003 - display->ramp) >> 1;
    if (panel->links.display->ramp >= 0x1000) {
        panel->links.display->ramp = 0x1000;
        NODE_HEADER(panel)->update_callback = poll_familiar_behavior_panel;
    }
    poll_familiar_behavior_panel(panel);
}

void populate_familiar_behavior_labels(CachedFamiliarBehaviorPanel *panel)
{
    s32 row = 0;
    SpritePartCommand *graphic = cached_behavior_row_graphic;

    panel->parts[1]->handler = cached_behavior_header_graphic;
    panel->parts[0]->handler = panel->packets;
    do {
        s32 number = row + 1;
        char buffer[16];
        char *text;

        panel->parts[row + 7]->handler = graphic;
        text = uint_to_dec_str(number, buffer);
        text = (char *)remap_flagged_string_bytes((u8 *)text);
        panel->parts[row + 2]->handler = build_positioned_text_glyphs((u8 *)&panel->packets->labels[row], (u8 *)text, 0);
        row = number;
    } while (row < 5);
    initialize_scaled_entry_cursor(&panel->cursor, &cached_behavior_cursor_template, (s32 *)panel->parts[12]);
}

void initialize_familiar_behavior_display(CachedFamiliarBehaviorPanel *panel,
                                                  ItemMenuDisplayLinks *links,
                                                  ItemMenuDisplayBlock *display,
                                                  ItemMenuDisplayPosition *position)
{
    MenuDisplayBlock *display_words = (MenuDisplayBlock *)display;
    DisplayPositionWords *vector_defaults = &display_vector_defaults;
    s32 first_position_word;

    display_words->words[0] = display_block_defaults.words[0];
    display_words->words[1] = display_block_defaults.words[1];
    display_words->words[2] = display_block_defaults.words[2];
    first_position_word = display_vector_defaults.unk0;
    display_words->words[3] = display_block_defaults.words[3];
    position->words.unk0 = first_position_word;
    position->words.unk4 = vector_defaults->unk4;
    position->words.unk8 = vector_defaults->unk8;
    links->display = display;
    links->position = position;
    links->unk_00 = 0;
    links->display->x = 72;
    links->display->y = -32;
    links->display->depth = 512;
    links->display->ramp = 0;
    links->position->position.offset_y = 40;
    links->display->mode = 4;
}

void position_familiar_behavior_cursor(CachedFamiliarBehaviorPanel *panel, s32 mode)
{
    panel->parts[12]->position->x = 39 - mode * 20;
}

void initialize_familiar_behavior_parts(CachedFamiliarBehaviorPanel *panel)
{
    s32 index;
    s32 plate_x;
    s32 label_x;
    s32 plate_y;
    s32 label_y;
    u8 shade;

    populate_familiar_behavior_labels(panel);
    index = 0;
    plate_y = 40;
    label_y = 136;
    shade = 95;
    label_x = 164;
    plate_x = plate_y;
    panel->parts[0]->position->y = 38;
    do {
        ItemMenuPartPosition *label;

        panel->parts[index + 7]->position->x = plate_x;
        panel->parts[index + 7]->position->y = plate_y;
        ((CachedMenuPartTransform *)panel->parts[index + 7]->vector)->x = plate_x;
        panel->parts[index + 2]->position->x = label_x;
        panel->parts[index + 2]->position->y = label_y;
        label = panel->parts[index + 2]->position;
        index++;
        plate_x -= 20;
        label->color.c.b = shade;
        label->color.c.g = shade;
        label->color.c.r = shade;
        label_x -= 20;
    } while (index < 5);
    panel->parts[12]->position->y = 54;
    position_familiar_behavior_cursor(panel, panel->selected_mode);
}

void initialize_familiar_behavior_request(CachedFamiliarBehaviorPanel *panel, ObjectNodeHeader *owner, ActorRecord *actor)
{
    s32 mode;

    panel->owner = owner;
    panel->actor = actor;
    panel->cursor_idle = 1;
    mode = actor->ai_mode;
    panel->transition_frames = 1;
    panel->selected_mode = 4 - mode;
    initialize_cached_compact_panel_rectangle(&panel->packets->backdrop);
}

void configure_familiar_behavior_panel(CachedFamiliarBehaviorPanel *panel, ObjectNodeHeader *owner, ActorRecord *actor)
{
    initialize_familiar_behavior_request(panel, owner, actor);
    initialize_familiar_behavior_display(panel, &panel->links, &panel->display, &panel->position);
    initialize_familiar_behavior_parts(panel);
}

s32 prepare_familiar_behavior_parts(CachedFamiliarBehaviorPanel *panel, s32 count)
{
    s32 ready = 0;
    u16 **resources = panel->resources;

    panel->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)resources, count, 12);
    if (panel->parts != 0) {
        DisplayPositionWords **banks = (DisplayPositionWords **)allocate_entry_slots((s32 *)resources, 5, 12);

        if (banks != 0) {
            bind_familiar_behavior_vectors(panel->parts, banks, &panel->part_vectors);
            panel->packets = (void *)(unsigned long)(u32)append_allocated_node_body((s32 *)resources, 12);
            ready = panel->packets != 0;
        }
    }
    return ready;
}

void complete_cached_message_transition(void *body)
{
    CachedFamiliarBehaviorPanel *panel = body;

    NODE_HEADER(panel)->flags |= OBJECT_REMOVE_PENDING;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    release_null_terminated_entries(panel->resources);
}

/* The reverse link builder stops at the first index equal to the part count. */
u8 cached_familiar_behavior_draw_order[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 0};
RECT cached_familiar_behavior_rectangle = {-60, -36, 120, 72};

void reorder_actor_choices(CachedActorChoice *choice)
{
    AnimatedSelectionEntry *ordered[2];
    s32 index;

    for (index = 0; index < choice->actor_count; index++) {
        ordered[index] = choice->entries[index];
    }
    sort_with_comparator((u8 *)ordered, choice->actor_count, sizeof(ordered[0]),
                            compare_selection_menu_entry_order);
    for (index = 0; index < choice->actor_count - 1; index++) {
        link_typed_list_node((ObjectNodeHeader *)ordered[index],
                             (ObjectNodeHeader *)ordered[index + 1]);
    }
    position_cached_actor_choice_entries(choice);
    shade_actor_choices(choice);
}

ObjectNodeHeader *create_familiar_behavior_panel(ObjectNodeHeader *owner, ActorRecord *actor)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedFamiliarBehaviorPanel *panel = NODE_BODY(node);

        if (prepare_familiar_behavior_parts(panel, 13) != 0) {
            set_message_mode(2);
            call_message_mode_handler();
            node->sprite = (SpriteFrameState *)&panel->links;
            panel->draw_chain = link_familiar_behavior_parts(panel->parts);
            configure_familiar_behavior_panel(panel, owner, actor);
            submit_script_with_registered_context((void *)cached_familiar_behavior_descriptions[panel->selected_mode]);
            NODE_HEADER(panel)->update_callback = advance_familiar_behavior_opening;
            register_node(node, draw_tinted_node_sprites_scratch);
            return node;
        }
        release_null_terminated_entries(panel->resources);
        node->flags |= OBJECT_REMOVE_PENDING;
        node = 0;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return node;
}

void release_actor_choice(ObjectNodeHeader *node)
{
    /* Form the raw body address without pointer arithmetic on a null node. */
    unsigned long body_address = (unsigned long)node + sizeof(*node);

    if (node != 0) {
        CachedActorChoice *choice = (CachedActorChoice *)body_address;
        s32 index = 0;

        do {
            if (choice->entries[index] != 0) {
                release_menu_entry_object((MenuEntryObject *)choice->entries[index]);
            }
            index++;
        } while (index < 2);
        {
            s32 global_flags = object_flag_block.flags;
            u16 node_flags = node->flags;

            node->flags = node_flags | OBJECT_REMOVE_PENDING;
            object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
        }
    }
}

void bind_familiar_behavior_vectors(ItemMenuPart **parts, DisplayPositionWords **banks,
                                            DisplayPositionWords *common)
{
    s32 index = 0;

    parts[0]->vector = common;
    parts[1]->vector = common;
    parts[12]->vector = common;
    do {
        /* The indexed offset is the first operand of the address addition. */
        ItemMenuPart **row_parts = &parts[index];

        row_parts[2]->vector = common;
        row_parts[7]->vector = &banks[(u32)index / 21][(u32)index % 21];
        index++;
    } while (index < 5);
}

void poll_familiar_behavior_panel(CachedFamiliarBehaviorPanel *panel)
{
    GameWork *input = &g_game_work;

    if (input->buttons != 0) {
        if (input->pressed_buttons & 0x40) {
            ObjectNodeHeader *node;

            SD_Call(AUDIO_ACCEPT);
            node = NODE_HEADER(panel);
            queue_menu_message(node);
            schedule_party_menu_resume(panel->owner);
            confirm_familiar_behavior(node);
        } else if (input->pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            queue_menu_message(NODE_HEADER(panel));
            schedule_party_menu_resume(panel->owner);
        } else if (input->buttons & 0xa000) {
            s32 movement = 0;
            s32 start_delay;

            /* A fresh press starts the same delay in either direction. */
            if (((input->pressed_buttons & 0x8000) && (start_delay = (movement = 1))) ||
                ((input->pressed_buttons & 0x2000) && (start_delay = 1, movement = -1))) {
                panel->repeat_delay = start_delay;
                panel->transition_frames = 4;
            } else if (panel->repeat_delay >= 4) {
                panel->repeat_delay -= 2;
                if (input->buttons & 0x8000) {
                    movement = 1;
                    panel->transition_frames = 3;
                } else if (input->buttons & 0x2000) {
                    movement = -1;
                    panel->transition_frames = 3;
                }
            } else {
                panel->repeat_delay++;
            }
            if (movement != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                panel->cursor_idle = 0;
                panel->transition_tick = 0;
                panel->previous_mode = panel->selected_mode;
                panel->selected_mode = advance_index_with_directional_clamp(panel->selected_mode, movement, 5);
                submit_script_with_registered_context((void *)cached_familiar_behavior_descriptions[panel->selected_mode]);
            }
        }
    }
    update_cached_familiar_behavior_motion(panel);
    if (panel->cursor_idle == 0 && advance_timed_tagged_stream(&panel->cursor) == 0) {
        panel->cursor_idle = 1;
    }
}

void initialize_cached_compact_panel_rectangle(CachedStoragePanelPacket *packet)
{
    build_panel_rectangle_packets(packet, &cached_familiar_behavior_rectangle);
    packet->closing_flags |= 0x80;
}

ItemMenuPart *link_familiar_behavior_parts(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts,
                                                       cached_familiar_behavior_draw_order, 13);
}
