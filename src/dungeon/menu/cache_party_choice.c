#include "dungeon/menu_cache.h"
#include "dungeon/menu_cache_actor_choice.h"
#include "engine/effect.h"
#include "engine/item.h"
#include "dungeon/menu_cache_party_menu.h"
#include "engine/node/allocation.h"
#include "shared/audio_commands.h"
#include "shared/game_work.h"
#include "slus.h"

/* Fade both linked actor entries using the two selection states. */
const u8 cached_party_shade_keys[2][2] = {{0, 1}, {1, 0}};
const SpriteColor cached_party_shade_colors[2] = {{0x00808080}, {0x00282828}};

/* Focus positions at the end of each of the two movement steps. */
const s16 cached_party_focus_positions[2][2] = {{212, 68}, {-236, -92}};
const s16 cached_party_focus_targets[2][2] = {{-236, 68}, {212, -92}};


void shade_party_choices(CachedPartyChoice *choice)
{
    s32 index;

    for (index = 0; index < choice->actor_count; index++) {
        AnimatedSelectionEntry *entry = choice->entries[index];
        const u8 *row = cached_party_shade_keys[index];
        s32 start = cached_party_shade_colors[row[choice->previous_index]].c.r;
        s32 end = cached_party_shade_colors[row[choice->selected_index]].c.r;
        s32 delta = (end - start) * choice->transition_tick / choice->transition_frames;
        MenuDisplayNode *node = entry->display;

        node->block->color.r = start + delta;
        node->block->color.g = node->block->color.r;
        node->block->color.b = node->block->color.r;
    }
}


/* Fill the selector from the active links on the primary actor. */
void initialize_party_choice(CachedPartyChoice *choice)
{
    fill_cached_choice_actors(choice->actors, &choice->actor_count);
}

/* Find the chosen actor in the selector list. */
/* Use the concrete body type so each selector keeps its original field offsets. */
s32 find_party_choice(CachedPartyChoice *choice, s32 actor_index)
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
void advance_party_choice_transition(CachedPartyChoice *choice)
{
    reorder_party_choices(choice);
    if (choice->transition_tick++ >= choice->transition_frames) {
        choice->animate = idle_party_choice;
    }
}

void spread_party_choices(CachedPartyChoice *choice)
{
    s32 index;

    if (choice->spacing >= 33) {
        choice->spacing = 32;
        choice->animate = idle_party_choice;
    }
    for (index = 0; index < choice->actor_count; index++) {
        MenuDisplayNode *node = choice->entries[index]->display;
        node->block->fields.x = choice->spacing * index - 92;
    }
    choice->spacing += (40 - choice->spacing) >> 3;
}


/* Reset the transition, wrap the selected index and refresh the preview. */
ObjectNodeHeader *begin_party_choice_change(CachedPartyChoice *choice, s32 delta)
{
    choice->transition_tick = 0;
    if (choice->animate == spread_party_choices) {
        choice->spacing = 32;
        spread_party_choices(choice);
    }
    choice->animate = advance_party_choice_transition;
    choice->previous_index = choice->selected_index;
    choice->selected_index = advance_index_with_single_wrap(choice->selected_index, delta, choice->actor_count);
    return refresh_party_choice_preview(choice->owner);
}

/* Retry the actor transition while the preview is being prepared. */
void resume_party_choice_transition(CachedPartyChoice *choice)
{
    if (begin_party_choice_change(choice, choice->pending_delta) != 0) {
        if (get_party_preview_mode(choice->owner) == 2) {
            s32 actor_index = get_menu_actor_index(choice->actors[choice->selected_index]);
            update_party_preview_target(choice->owner, actor_index);
        }
        NODE_HEADER(choice)->update_callback = update_party_choice;
    }
}

/* Read controller input and start the selected actor preview. */
void poll_party_choice_input(CachedPartyChoice *choice)
{
    GameWork *input;
    s32 delta;

    input = &g_game_work;
    delta = 0;
    if (input->buttons != 0) {
        READ_CACHED_CHOICE_DIRECTION(choice, input, delta);
        if (delta != 0) {
            SD_Call(AUDIO_CURSOR_MOVE);
            if (begin_party_choice_change(choice, delta) == 0) {
                choice->pending_delta = delta;
                NODE_HEADER(choice)->update_callback = resume_party_choice_transition;
            } else if (get_party_preview_mode(choice->owner) == 2) {
                s32 actor_index = get_menu_actor_index(choice->actors[choice->selected_index]);
                update_party_preview_target(choice->owner, actor_index);
            }
        }
    }
}

/* Run both active animations before reading the controller. */
void update_party_choice(CachedPartyChoice *choice)
{
    if (choice->animate != 0) {
        choice->animate(choice);
    }
    if (choice->after_animate != 0) {
        choice->after_animate(choice);
    }
    poll_party_choice_input(choice);
}

/* Return the actor ID selected in the preview panel. */
s32 get_party_choice_selection(ObjectNodeHeader *node)
{
    CachedPartyChoice *choice = NODE_BODY(node);

    return get_menu_actor_index(choice->actors[choice->selected_index]);
}

s32 initialize_party_choice_entries(CachedPartyChoice *choice)
{
    if (choice->actor_count > 0) {
        s32 index = 0;
        const u8 (*keys)[2] = cached_party_shade_keys;

        do {
            s32 slot = index + 1;
            s32 key = keys[choice->selected_index][index];

            choice->entries[index] = (AnimatedSelectionEntry *)allocate_menu_entry_object(choice->actors[index], slot,
                    choice->spacing * index - 92, key * 12 - 96, 512 + key * 30);
            if (choice->entries[index] == 0) {
                return 0;
            }
            index = slot;
        } while (index < choice->actor_count);
    }
    choice->transition_tick = 1;
    choice->transition_frames = 1;
    reorder_party_choices(choice);
    return 1;
}

ObjectNodeHeader *create_party_actor_choice(ObjectNodeHeader *owner, s32 actor_index)
{
    ObjectNodeHeader *node = allocate_flagged_object_node(0);

    if (node != 0) {
        CachedPartyChoice *choice = NODE_BODY(node);

        initialize_party_choice(choice);
        choice->selected_index = find_party_choice(choice, actor_index);
        choice->directional_enabled = 1;
        choice->owner = owner;
        node->update_callback = update_party_choice;
        choice->animate = spread_party_choices;
        if (initialize_party_choice_entries(choice) == 0) {
            release_party_actor_choice(node);
            node = 0;
        }
    }
    return node;
}

void enable_party_choice_input(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedPartyChoice *choice = NODE_BODY(node);
        choice->directional_enabled = 1;
    }
}

void disable_party_choice_input(ObjectNodeHeader *node)
{
    if (node != 0) {
        CachedPartyChoice *choice = NODE_BODY(node);
        choice->directional_enabled = 0;
    }
}

void place_party_choice_focus(CachedPartyChoice *choice)
{
    s32 row = 0;

    if (choice->actor_count > 0) {
        const s16 (*positions)[2] = cached_party_focus_positions;

        do {
            /* The indexed offset is the first operand of the address addition. */
            const s16 *column = (const s16 *)(choice->focus_column * sizeof(*positions) +
                                              (unsigned long)positions);
            s32 step = choice->focus_step;
            s32 x = column[step - 2];
            MenuDisplayBlock *block = choice->entries[row]->display->block;

            if (row != 0) {
                x += choice->spacing;
            }
            block->fields.x = x;
            row++;
        } while (row < choice->actor_count);
    }
}

void advance_party_choice_focus(CachedPartyChoice *choice)
{
    if (choice->focus_ticks > 0) {
        ease_cached_party_choice_focus(choice);
        choice->focus_ticks--;
    } else {
        choice->focus_step++;
        if (choice->focus_step < 3) {
            place_party_choice_focus(choice);
            choice->focus_ticks = 16;
        } else {
            place_party_choice_focus(choice);
            choice->focus_step = 0;
            choice->after_animate = 0;
        }
    }
}

ActorRecord *get_party_choice_actor(ObjectNodeHeader *node)
{
    CachedPartyChoice *choice = NODE_BODY(node);

    return choice->actors[choice->selected_index];
}

void reorder_party_choices(CachedPartyChoice *choice)
{
    AnimatedSelectionEntry *ordered[2];
    s32 index;

    for (index = 0; index < choice->actor_count; index++) {
        ordered[index] = choice->entries[index];
    }
    position_cached_party_choice_entries(choice);
    shade_party_choices(choice);
    sort_with_comparator((u8 *)ordered, choice->actor_count, sizeof(ordered[0]),
                            compare_selection_menu_entry_order_for_party);
    for (index = 0; index < choice->actor_count - 1; index++) {
        link_typed_list_node((ObjectNodeHeader *)ordered[index],
                             (ObjectNodeHeader *)ordered[index + 1]);
    }
}

void release_party_actor_choice(ObjectNodeHeader *node)
{
    /* Form the raw body address without pointer arithmetic on a null node. */
    unsigned long body_address = (unsigned long)node + sizeof(*node);

    if (node != 0) {
        CachedPartyChoice *choice = (CachedPartyChoice *)body_address;
        s32 index = 0;
        s32 global_flags = object_flag_block.flags;
        u16 flags = node->flags;

        node->flags = flags | OBJECT_REMOVE_PENDING;
        object_flag_block.flags = global_flags | OBJECT_REMOVE_PENDING;
        do {
            if (choice->entries[index] != 0) {
                release_menu_entry_object((MenuEntryObject *)choice->entries[index]);
            }
            index++;
        } while (index < 2);
    }
}

void start_party_choice_focus(ObjectNodeHeader *node, s32 column)
{
    /* Form the raw body address without pointer arithmetic on a null node. */
    CachedPartyChoice *choice = (CachedPartyChoice *)((unsigned long)node + sizeof(*node));

    if (node != 0) {
        void (*callback)(CachedPartyChoice *) = choice->animate;

        if (callback == spread_party_choices) {
            choice->animate = idle_party_choice;
        }
        if (choice->focus_step != 0) {
            if (choice->focus_column != column) {
                choice->focus_step = 3 - choice->focus_step;
                choice->focus_ticks = 16 - choice->focus_ticks;
            }
        } else {
            choice->focus_step = 1;
            choice->focus_ticks = 16;
        }
        choice->focus_column = column;
        choice->after_animate = advance_party_choice_focus;
    }
}
