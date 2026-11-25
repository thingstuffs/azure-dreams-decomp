#include "sdk/libc.h"
#include "engine/sprite.h"
#include "engine/texture.h"
#include "engine/menu.h"
#include "dungeon/menu_cache_linked_actor.h"
#include "dungeon/menu_cache_actor_choice.h"
#include "dungeon/item.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu_cache_paged.h"
#include "dungeon/menu/state.h"
#include "dungeon/menu_cache_selection.h"
#include "engine/entity/effect_slots.h"
#include "engine/util.h"
#include "sdk/libgpu_types.h"
#include "sdk/strcpy.h"
#include "shared/actor_action_flags.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "script_symbols.h"
#include "engine/object.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/def_table.h"
#include "shared/menu_display.h"
#include "engine/effect.h"
#include "engine/node/allocation.h"
#include "shared/monster_ids.h"
#include "slus.h"

void show_cached_linked_actor_notice(void)
{
    build_object_registration_script(cached_no_linked_actor_notice);
}

/* Allocate the group and create the selector and command panel together. */
ObjectNodeHeader *create_linked_actor_menu(ObjectNodeHeader *owner, s32 position, s32 preserve_owner)
{
    ObjectNodeHeader *node = allocate_list_node(0, &owner->next);

    if (node != 0) {
        CachedLinkedActorMenu *menu = NODE_BODY(node);

        clear_win_sw0_resident_bit();
        menu->owner_link.owner = owner;
        menu->preserve_owner = preserve_owner;
        clear_dungeon_menu_flag();
        if (get_menu_actor_mask() != 0) {
            menu->actor_choice = create_cached_linked_actor_selector(node, position);
            menu->command_panel = create_cached_linked_actor_panel(node, position);
            node->update_callback = 0;
            if (menu->actor_choice == 0 || menu->command_panel == 0) {
                release_cached_linked_actor_children(menu);
                node->flags |= OBJECT_REMOVE_PENDING;
                node = 0;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        } else {
            node->update_callback = check_cached_linked_actor_close_signal;
            set_message_mode(1);
            call_message_mode_handler();
            show_cached_linked_actor_notice();
        }
    }
    return node;
}

/* Open the menu and close its owner when the selected action finishes. */
ObjectNodeHeader *open_linked_actor_menu(ObjectNodeHeader *owner, s32 position)
{
    return create_linked_actor_menu(owner, position, 0);
}

ObjectNodeHeader *create_linked_actor_submenu(ObjectNodeHeader *owner, s32 position)
{
    return create_linked_actor_menu(owner, position, 1);
}

/* Release both child selectors and clear the actor preview markers. */
void release_cached_linked_actor_children(CachedLinkedActorMenu *menu)
{
    release_actor_choice(menu->actor_choice);
    release_cached_linked_actor_panel(menu->command_panel);
    set_dungeon_menu_flag_if_idle();
    update_selection_tile_markers(0, 0);
    enqueue_script_message_command();
}

void *ensure_cached_linked_actor_close(CachedMenuOwnerLink *link)
{
    void *selection = ensure_selection_menu_and_register_draw(link->owner);

    if (selection != 0) {
        NODE_HEADER(link)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
    return selection;
}

void start_cached_linked_actor_close(CachedLinkedActorMenu *menu)
{
    release_cached_linked_actor_children(menu);
    if (menu->preserve_owner == 0) {
        if (ensure_cached_linked_actor_close(&menu->owner_link) == 0) {
            NODE_HEADER(menu)->update_callback = ensure_cached_linked_actor_close;
        }
    } else {
        NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

void finish_cached_linked_actor_cleanup(CachedLinkedActorMenu *menu)
{
    s32 flags;
    s32 preserve_owner;

    release_cached_linked_actor_children(menu);
    NODE_HEADER(menu)->flags |= OBJECT_REMOVE_PENDING;
    flags = object_flag_block.flags;
    preserve_owner = menu->preserve_owner;
    object_flag_block.flags = flags | OBJECT_REMOVE_PENDING;
    if (!preserve_owner) {
        destroy_selection_menu_and_release_owner(menu->owner_link.owner);
    }
}

void set_cached_actor_preview_target(ObjectNodeHeader *node, s32 actor_index)
{
    if (node != 0) {
        CachedLinkedActorMenu *menu = NODE_BODY(node);
        begin_actor_command_update(menu->command_panel, actor_index);
    }
}

void reset_cached_linked_actor_preview(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedLinkedActorMenu *menu = NODE_BODY(node);
        reset_actor_command_panel(menu->command_panel);
    }
}

/* Find the matching species and command variant before the table terminator. */
const CachedActorActionText *find_cached_actor_action_text(const ActorRecord *actor, s32 variant)
{
    s32 row;
    for (row = 0; cached_linked_actor_action_text[row].species != 0; row++) {
        const CachedActorActionText *entry = &cached_linked_actor_action_text[row];
        if (entry->species == actor->species && entry->variant == variant) {
            return entry;
        }
    }
    return 0;
}

const char *get_cached_actor_action_label(const ActorRecord *actor, s32 variant)
{
    return find_cached_actor_action_text(actor, variant)->label;
}

const char *get_cached_actor_action_description(const ActorRecord *actor, s32 variant)
{
    return find_cached_actor_action_text(actor, variant)->description;
}

static const u8 linked_actor_grid_draw_order[] __attribute__((aligned(4))) = {
    0, 1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 38, 39, 40, 41, 42, 43,
    44, 45, 46, 47, 48, 49, 50,
};
static const u8 linked_actor_panel_draw_order[] __attribute__((aligned(4))) = {0, 1, 50};

ItemMenuPart *link_cached_actor_grid_parts(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts, (u8 *)linked_actor_grid_draw_order, 50);
}

ItemMenuPart *link_cached_actor_panel_parts(ItemMenuPart **parts)
{
    return (ItemMenuPart *)build_reverse_indexed_chain((struct S_800491F4 **)parts, (u8 *)linked_actor_panel_draw_order, 50);
}

const RECT cached_actor_command_panel_rectangle __attribute__((aligned(4))) = {-68, -8, 136, 16};

/* The imported text bank supplies both strings in each species and variant row. */
CachedActorActionText cached_linked_actor_action_text[28] = {
    {MONSTER_SABER, 0, cached_linked_actor_strings + 0x76c, cached_linked_actor_strings + 0x72c},
    {MONSTER_SNOWMAN, 0, cached_linked_actor_strings + 0x76c, cached_linked_actor_strings + 0x6ec},
    {MONSTER_NOISE, 0, cached_linked_actor_strings + 0x6cc, cached_linked_actor_strings + 0x6a8},
    {MONSTER_U_BOAT, 0, cached_linked_actor_strings + 0x69c, cached_linked_actor_strings + 0x66c},
    {MONSTER_U_BOAT, 1, cached_linked_actor_strings + 0x64c, cached_linked_actor_strings + 0x618},
    {MONSTER_BALOON, 0, cached_linked_actor_strings + 0x610, cached_linked_actor_strings + 0x5d8},
    {MONSTER_DREAMIN, 0, cached_linked_actor_strings + 0x5c4, cached_linked_actor_strings + 0x590},
    {MONSTER_BLUME, 0, cached_linked_actor_strings + 0x57c, cached_linked_actor_strings + 0x558},
    {MONSTER_VOLCANO, 0, cached_linked_actor_strings + 0x53c, cached_linked_actor_strings + 0x518},
    {MONSTER_CYCLONE, 0, cached_linked_actor_strings + 0x4fc, cached_linked_actor_strings + 0x4fc},
    {MONSTER_MANOEVA, 0, cached_linked_actor_strings + 0x4e8, cached_linked_actor_strings + 0x4a8},
    {MONSTER_MANOEVA, 1, cached_linked_actor_strings + 0x484, cached_linked_actor_strings + 0x448},
    {MONSTER_BARONG, 0, cached_linked_actor_strings + 0x430, cached_linked_actor_strings + 0x3f4},
    {MONSTER_PICKET, 0, cached_linked_actor_strings + 0x3d4, cached_linked_actor_strings + 0x3a0},
    {MONSTER_PICKET, 1, cached_linked_actor_strings + 0x38c, cached_linked_actor_strings + 0x358},
    {MONSTER_WEADOG, 0, cached_linked_actor_strings + 0x340, cached_linked_actor_strings + 0x30c},
    {MONSTER_STEALTH, 0, cached_linked_actor_strings + 0x2f8, cached_linked_actor_strings + 0x2b8},
    {MONSTER_VIPER, 0, cached_linked_actor_strings + 0x2ac, cached_linked_actor_strings + 0x278},
    {MONSTER_NAPLASS, 0, cached_linked_actor_strings + 0x26c, cached_linked_actor_strings + 0x234},
    {MONSTER_ZU, 0, cached_linked_actor_strings + 0x21c, cached_linked_actor_strings + 0x1e4},
    {MONSTER_MANDARA, 0, cached_linked_actor_strings + 0x1d8, cached_linked_actor_strings + 0x1b0},
    {MONSTER_KILLER, 0, cached_linked_actor_strings + 0x198, cached_linked_actor_strings + 0x170},
    {MONSTER_GARUDA, 0, cached_linked_actor_strings + 0x160, cached_linked_actor_strings + 0x120},
    {MONSTER_GLACIER, 0, cached_linked_actor_strings + 0x104, cached_linked_actor_strings + 0x0c4},
    {MONSTER_TYRANT, 0, cached_linked_actor_strings + 0x0b4, cached_linked_actor_strings + 0x090},
    {MONSTER_GOLEM, 0, cached_linked_actor_strings + 0x070, cached_linked_actor_strings + 0x038},
    {MONSTER_BALOON, 0, cached_linked_actor_strings + 0x610, cached_linked_actor_strings + 0x000},
    {0, 0, 0, 0},
};

void reset_actor_command_row_positions(CachedLinkedActorPanel *panel)
{
    s32 row = 0;

    do {
        panel->parts[row + 26]->position->x = 77;
        panel->parts[row + 26]->position->color.c.r = 104;
        panel->parts[row + 26]->position->color.c.g = 104;
        panel->parts[row + 26]->position->color.c.b = 96;
        panel->parts[row + 2]->position->x = 9;
        panel->parts[row + 14]->position->x = 145;
        panel->parts[row + 38]->position->x = 143;
        row++;
    } while (row < 12);
}

s32 is_actor_command_input_disabled(ActorRecord *actor)
{
    s32 disabled;

    if (actor->flags1C & ACTOR_PLAYER_AWARE) {
        disabled = (s16)get_entity_effect_value(actor, STATUS_BRAINWASH) != 0;
    } else {
        disabled = 1;
    }
    return disabled;
}

void run_actor_command_input(CachedLinkedActorPanel *panel)
{
    poll_actor_command_panel(panel);
}

void advance_actor_command_grid_opening(CachedLinkedActorPanel *panel)
{
    poll_actor_command_panel(panel);
    panel->links.display->ramp = panel->opening_step * 1024;
    panel->opening_step++;
    if (panel->opening_step >= 5) {
        panel->opening_step = 0;
        panel->draw_chain = link_cached_actor_grid_parts(panel->parts);
        NODE_HEADER(panel)->update_callback = finish_actor_command_grid_opening;
    }
}

s32 prepare_actor_command_parts(CachedLinkedActorPanel *panel, s32 count)
{
    s32 ready = 0;
    u16 **resources = panel->resources;

    panel->parts = (ItemMenuPart **)rebuild_pointer_pool((s32 *)resources, count, 12);
    if (panel->parts != 0) {
        DisplayPositionWords **vectors = (DisplayPositionWords **)allocate_entry_slots((s32 *)resources, 12, 12);

        if (vectors != 0) {
            panel->panel_packets = (void *)(unsigned long)(u32)append_allocated_node_body((s32 *)resources, 12);
            if (panel->panel_packets != 0) {
                panel->part_vectors.unk0 = display_vector_defaults.unk0;
                panel->part_vectors.unk4 = display_vector_defaults.unk4;
                panel->part_vectors.unk8 = display_vector_defaults.unk8;
                bind_actor_command_part_vectors(panel->parts, vectors, &panel->part_vectors);
                ready = 1;
            }
        }
    }
    return ready;
}

void initialize_actor_command_background(CachedLinkedActorPanel *panel, ItemMenuDisplayLinks *links,
                                                ItemMenuDisplayBlock *display, ItemMenuDisplayPosition *position)
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
    links->display->x = 2;
    links->display->y = -104;
    links->display->depth = 512;
    links->display->ramp = 0;
    links->display->mode = 4;
}

void *create_actor_command_description(s32 action, ActorRecord *actor)
{
    char text[64];
    s32 slot;
    slot = action - 1;
    if ((u32)slot < 3) {
        strcpy(text, cached_actor_command_descriptions[0]);
        strcat(text, (const char *)item_action_definitions[actor->abilities[slot].id].normal_name);
    } else if ((u32)(slot = action - 5) < 3) {
        strcpy(text, cached_actor_command_descriptions[1]);
        strcat(text, (const char *)item_action_definitions[actor->abilities[slot].id].normal_name);
    } else if (action == 0) {
        strcpy(text, cached_actor_command_descriptions[2]);
    } else if (action == 12) {
        strcpy(text, cached_actor_command_descriptions[3]);
    } else if (action == 9) {
        strcpy(text, get_cached_actor_action_description(actor, 0));
    } else if (action == 10) {
        strcpy(text, get_cached_actor_action_description(actor, 1));
    } else if (action == 8) {
        strcpy(text, cached_actor_command_descriptions[4]);
    } else if (action == 11) {
        strcpy(text, cached_actor_command_descriptions[5]);
    }

    return create_label_glyph_entries(text, 1);
}

void populate_actor_command_descriptions(CachedLinkedActorPanel *panel, ActorRecord *actor)
{
    s32 row;

    panel->parts[0]->handler = get_menu_count_template(panel->action_count);
    {
        ItemMenuPart *cursor = panel->parts[1];
        cursor->handler = is_actor_command_input_disabled(actor) == 0 ? menu_leaf_template_6 : 0;
    }
    row = 0;
    if (row < panel->action_count) {
        u8 *left_template = cached_selection_row_left_template;
        u8 *right_template = cached_selection_row_middle_template;

        do {
            void *label;

            panel->parts[row + 2]->handler = left_template;
            panel->parts[row + 14]->handler = right_template;
            panel->parts[row + 26]->handler = panel->panel_packets;
            label = create_actor_command_description(panel->action_ids[row + 1], actor);
            panel->parts[row + 38]->handler = label;
            row++;
        } while (row < panel->action_count);
    }
}

s32 build_actor_command_options(CachedLinkedActorPanel *panel, u8 *actions, ActorRecord *actor)
{
    s32 count = 2;

    actions[0] = 11;
    actions[1] = 8;
    if ((s16)get_entity_effect_value(actor, STATUS_MAGIC_BIND) == 0) {
        s32 ability_slot = 0;
        u8 *next_action = &actions[count];

        do {
            if (actor->abilities[ability_slot].id != 0) {
                *next_action++ = ability_slot + 1;
                *next_action++ = ability_slot + 5;
                count += 2;
            }
            ability_slot++;
        } while (ability_slot < 3);
    }
    if (panel->has_primary_action != 0) {
        actions[count++] = 9;
    }
    if (panel->has_secondary_action != 0) {
        actions[count++] = 10;
    }
    actions[count] = 12;
    return count + 1;
}

s32 count_actor_command_abilities(ActorRecord *actor)
{
    s32 available = 0;
    s32 slot = available;

    do {
        if (actor->abilities[slot].id != 0) {
            available++;
        }
        slot++;
    } while (slot < 3);
    return available;
}

void configure_actor_command_panel(CachedLinkedActorPanel *panel, ObjectNodeHeader *owner, s32 actor_index)
{
    initialize_cached_actor_command_request(panel, owner, actor_index);
    initialize_actor_command_background(panel, &panel->links, &panel->display, &panel->position);
    initialize_actor_command_row_layout(panel);
}

void clear_actor_command_labels(CachedLinkedActorPanel *panel)
{
    s32 row = 0;

    do {
        flag_optional_object_for_removal(panel->parts[row + 38]->handler);
        panel->parts[row + 38]->handler = 0;
        row++;
    } while (row < 12);
}

void release_cached_linked_actor_panel(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedLinkedActorPanel *panel = NODE_BODY(node);

        clear_actor_command_labels(panel);
        release_null_terminated_entries(panel->resources);
        enqueue_script_message_command();
        {
            s32 global_flags = object_flag_block.flags;
            u16 node_flags = node->flags;

            node->flags = node_flags | OBJECT_REMOVE_PENDING;
            object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
        }
    }
}

void clear_actor_command_parts(CachedLinkedActorPanel *panel)
{
    s32 index = 0;

    do {
        panel->parts[index]->handler = 0;
        index++;
    } while (index < 50);
}

void restart_actor_command_panel(CachedLinkedActorPanel *panel)
{
    clear_actor_command_labels(panel);
    clear_actor_command_parts(panel);
    panel->draw_chain = link_cached_actor_panel_parts(panel->parts);
    configure_actor_command_panel(panel, panel->owner, panel->actor_index);
    NODE_HEADER(panel)->update_callback = advance_actor_command_grid_opening;
}

void begin_actor_command_update(ObjectNodeHeader *node, s32 actor_index)
{
    if (node != 0) {
        CachedLinkedActorPanel *panel = NODE_BODY(node);

        panel->actor_index = actor_index;
        node->update_callback = animate_actor_command_change;
    }
}

void reset_actor_command_panel(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedLinkedActorPanel *panel = NODE_BODY(node);

        if (node->update_callback != animate_actor_command_change) {
            apply_actor_command(panel);
        }
    }
}

const char *get_actor_command_hint(s32 action, ActorRecord *actor)
{
    s32 slot = action - 1;

    if ((u32)slot < 3) {
        const DefEntry *definitions = item_action_definitions;
        return (const char *)definitions[actor->abilities[slot].id].normal_description;
    }
    slot = action - 5;
    if ((u32)slot < 3) {
        const DefEntry *definitions = item_action_definitions;
        s32 alternate = resolve_alternate_spell_id(actor->abilities[slot].id);
        return (const char *)definitions[alternate].alternate_description;
    }
    if (action == 8) {
        return cached_actor_direct_attack_hint;
    }
    if (action == 11) {
        return cached_actor_current_direction_move_hint;
    }
    if (action == 9) {
        return get_cached_actor_action_label(actor, 0);
    }
    if (action == 10) {
        return get_cached_actor_action_label(actor, 1);
    }
    {
        const char *label;
        if (action != 12) {
            label = cached_actor_command_unavailable_hint;
        } else {
            label = cached_actor_stay_hint;
        }
        return label;
    }
}

void finish_actor_command_grid_opening(CachedLinkedActorPanel *panel)
{
    s32 row;

    poll_actor_command_panel(panel);
    row = 0;
    if (panel->action_count > 0) {
        do {
            CachedMenuPartTransform *transform = (CachedMenuPartTransform *)panel->parts[row + 38]->vector;
            transform->rotation_x = 1024 - (panel->opening_step + 1) * 256;
            row++;
        } while (row < panel->action_count);
    }

    panel->opening_step++;
    if (panel->opening_step >= 4) {
        panel->opening_step = 0;
        NODE_HEADER(panel)->update_callback = run_actor_command_input;
    }
}

void animate_actor_command_change(CachedLinkedActorPanel *panel)
{
    s32 row = 0;

    if (panel->action_count > 0) {
        do {
            CachedMenuPartTransform *transform = (CachedMenuPartTransform *)panel->parts[row + 38]->vector;
            transform->rotation_x = -panel->opening_step * 256;
            row++;
        } while (row < panel->action_count);
    }
    panel->opening_step++;
    if (panel->opening_step >= 5) {
        panel->opening_step = 0;
        restart_actor_command_panel(panel);
        update_selection_tile_markers(panel->actor, panel->action_ids[panel->selected_row + 1]);
    }
}

void initialize_actor_command_row_layout(CachedLinkedActorPanel *panel)
{
    s32 row = 0;

    panel->parts[0]->position->y = panel->action_count * 8 + 2;
    if (panel->action_count > 0) {
        s32 vector_y = 8;
        s32 row_y = 10;
        s32 text_y = 130;

        do {
            CachedMenuPartTransform *transform;

            panel->parts[row + 38]->position->x = 142;
            panel->parts[row + 38]->position->y = text_y;
            panel->parts[row + 2]->position->x = 9;
            panel->parts[row + 2]->position->y = row_y;
            panel->parts[row + 14]->position->x = 145;
            panel->parts[row + 14]->position->y = row_y;
            panel->parts[row + 26]->position->x = 77;
            panel->parts[row + 26]->position->y = row_y;
            ((CachedMenuPartTransform *)panel->parts[row + 26]->vector)->y = vector_y;
            transform = (CachedMenuPartTransform *)panel->parts[row + 26]->vector;
            transform->rotation_x = 1024;
            row++;
            text_y += 16;
            row_y += 16;
            vector_y += 16;
        } while (row < panel->action_count);
    }
    panel->transition_frames = 1;
    panel->transition_tick = 1;
    reset_actor_command_row_positions(panel);
}

ObjectNodeHeader *create_cached_linked_actor_panel(ObjectNodeHeader *owner, s32 actor_index)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedLinkedActorPanel *panel = NODE_BODY(node);

        if (prepare_actor_command_parts(panel, 50) != 0) {
            node->sprite = (SpriteFrameState *)&panel->links;
            panel->draw_chain = link_cached_actor_panel_parts(panel->parts);
            set_message_mode(2);
            call_message_mode_handler();
            save_cached_linked_actor_action_flags(panel);
            configure_actor_command_panel(panel, owner, actor_index);
            NODE_HEADER(panel)->update_callback = advance_actor_command_grid_opening;
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

void save_cached_linked_actor_action_flags(CachedLinkedActorPanel *panel)
{
    s32 slot = 0;
    ActorRecord *player = primary_actor_record;
    const u8 *base = (const u8 *)player;

    do {
        ActorRecord *actor = read_cached_familiar_link(base);

        if (actor != 0) {
            panel->saved_action_flags[slot] = actor->action_flags;
        }
        slot++;
        base += sizeof(player->unk_AC.address);
    } while (slot < 2);
}

void restore_cached_linked_actor_action_flags(CachedLinkedActorPanel *panel)
{
    s32 slot = 0;
    ActorRecord *player = primary_actor_record;
    const u8 *base = (const u8 *)player;

    do {
        ActorRecord *actor = read_cached_familiar_link(base);

        if (actor != 0) {
            actor->action_flags = panel->saved_action_flags[slot];
        }
        slot++;
        base += sizeof(player->unk_AC.address);
    } while (slot < 2);
}

void apply_actor_command(CachedLinkedActorPanel *panel)
{
    ActorRecord *actor = get_cached_player_familiar(panel->actor_index);
    DungeonMenuItemSelection *selection = &selected_item_record_alias;
    s32 slot;
    s32 action = panel->action_ids[panel->selected_row + 1];

    actor->action_flags = action & 0x3F;
    slot = panel->actor_index;
    selection->request = 12;
    /* Request 12 passes the familiar slot in the item word. */
    selected_item_record_alias.item = (DungeonItemEntry *)(long)slot;
    if (action != 0) {
        append_packed_action_record(actor, 128, (s16)panel->actor_index, (s16)actor->action_flags);
        actor->action_flags |= ACTOR_ACTION_PENDING;
    }
}

s32 find_actor_command_row(CachedLinkedActorPanel *panel, ActorRecord *actor)
{
    s32 row;
    s32 action;

    if (is_actor_command_input_disabled(actor) != 0) {
        return -1;
    }
    action = (u8)actor->action_flags;
    for (row = 0; row < panel->action_count; row++) {
        if (panel->action_ids[row + 1] == action) {
            break;
        }
    }
    if (row == panel->action_count) {
        row = 0;
    }
    return row;
}

void poll_actor_command_panel(CachedLinkedActorPanel *panel)
{
    GameWork *input = &g_game_work;

    if (input->buttons != 0) {
        if (is_actor_command_input_disabled(get_cached_player_familiar(panel->actor_index))) {
            if (input->pressed_buttons & 0x20) {
                SD_Call(AUDIO_CANCEL);
                restore_cached_linked_actor_action_flags(panel);
                schedule_cached_linked_actor_close(panel->owner);
            }
            return;
        }
        if (input->pressed_buttons & 0x20) {
            SD_Call(AUDIO_CANCEL);
            restore_cached_linked_actor_action_flags(panel);
            schedule_cached_linked_actor_close(panel->owner);
        } else if (input->pressed_buttons & 0x40) {
            SD_Call(AUDIO_ACCEPT);
            apply_actor_command(panel);
            schedule_cached_linked_actor_cleanup(panel->owner);
        } else if (input->buttons & 0x5000) {
            s32 step = 0;

            if (input->pressed_buttons & 0x4000) {
                step = 1;
                panel->repeat_delay = 0;
                panel->transition_frames = 3;
            } else if (input->pressed_buttons & 0x1000) {
                step = -1;
                panel->repeat_delay = 0;
                panel->transition_frames = 3;
            } else if (panel->repeat_delay >= 3) {
                panel->repeat_delay--;
                if (input->buttons & 0x4000) {
                    step = 1;
                    panel->transition_frames = 2;
                } else if (input->buttons & 0x1000) {
                    step = -1;
                    panel->transition_frames = 2;
                }
            } else {
                panel->repeat_delay++;
            }
            if (step != 0) {
                SD_Call(AUDIO_CURSOR_MOVE);
                panel->transition_tick = 0;
                panel->previous_row = panel->selected_row;
                panel->selected_row = advance_index_with_single_wrap(panel->selected_row, step, panel->action_count);
                submit_script_with_registered_context((void *)get_actor_command_hint(panel->action_ids[panel->selected_row + 1], panel->actor));
                update_selection_tile_markers(panel->actor, panel->action_ids[panel->selected_row + 1]);
            }
        }
    }
    update_cached_actor_command_row_motion(panel);
}

void bind_actor_command_part_vectors(ItemMenuPart **parts, DisplayPositionWords **banks,
                                            DisplayPositionWords *common)
{
    s32 index = 0;

    parts[0]->vector = common;
    parts[1]->vector = common;
    do {
        /* The indexed offset is the first operand of the address addition. */
        ItemMenuPart **row_parts = (ItemMenuPart **)(index * sizeof(*parts) + (unsigned long)parts);

        row_parts[26]->vector = &banks[(u32)index / 21][(u32)index % 21];
        row_parts[2]->vector = row_parts[26]->vector;
        row_parts[14]->vector = row_parts[26]->vector;
        row_parts[38]->vector = row_parts[26]->vector;
        index++;
    } while (index < 12);
}

void schedule_cached_linked_actor_close(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = start_cached_linked_actor_close;
    }
}

void schedule_cached_linked_actor_cleanup(ObjectNodeHeader *node)
{
    if (node != 0) {
        node->update_callback = finish_cached_linked_actor_cleanup;
    }
}

void poll_cached_linked_actor_cancel(void *body)
{
    if (g_game_work.buttons != 0 && (g_game_work.pressed_buttons & 0x20)) {
        SD_Call(AUDIO_CANCEL);
        schedule_cached_linked_actor_close(NODE_HEADER(body));
    }
}

void check_cached_linked_actor_close_signal(void *body)
{
    if (test_resident_bitmap_bit(sn_win_sw0) != 0) {
        clear_resident_bitmap_bit(sn_win_sw0);
        schedule_cached_linked_actor_close(NODE_HEADER(body));
    } else {
        poll_cached_linked_actor_cancel(body);
    }
}

void initialize_linked_actor_panel_packets(void *packets)
{
    init_packet_pair_and_gradient(packets, (void *)&cached_actor_command_panel_rectangle);
}
