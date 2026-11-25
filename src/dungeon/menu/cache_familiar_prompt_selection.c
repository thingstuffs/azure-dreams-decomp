#include "dungeon/menu_cache_stats.h"
#include "dungeon/menu_cache.h"
#include "engine/item.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "dungeon/menu_cache_paged.h"
#include "engine/menu.h"
#include "engine/object.h"
#include "shared/audio_commands.h"
#include "shared/game_state.h"
#include "shared/game_work.h"
#include "shared/item_ids.h"
#include "slus.h"

DungeonItemEntry *find_familiar_assignment_item(ActorRecord *actor)
{
    DungeonItemEntry *found = 0;
    s32 slot = 0;

    do {
        if ((ActorRecord *)(unsigned long)(u32)resolve_familiar_slot_value(slot) == actor) {
            s32 index = 0;

            do {
                DungeonItemEntry *item = GAME_STATE->item_list[index];

                if (item != 0 && item->kind == ITEM_KIND_FAMILIAR
                    && (item->unk_03 & 0x1f) == slot) {
                    found = item;
                    break;
                }
                index++;
            } while (index < 20);
            break;
        }
        slot++;
    } while (slot < 20);
    return found;
}

ObjectNodeHeader *begin_familiar_assignment(CachedFamiliarPrompt *prompt)
{
    s32 index = prompt->selected_actor_index;
    s32 y = (index % 5) * 24 - 128;
    DungeonItemEntry *item = find_familiar_assignment_item(prompt->actors[index]);

    return create_familiar_assignment_menu(prompt->owner, prompt->selected_actor_index,
                                                  0, -180, y, item, prompt->assignment_slot);
}

s32 collect_familiar_actors(DungeonItemEntry **items, ActorRecord **actors)
{
    s32 count = 0;

    while (*items != 0) {
        if ((*items)->kind == ITEM_KIND_FAMILIAR) {
            count++;
            *actors = (ActorRecord *)(unsigned long)(u32)resolve_item_record_slot_value(*items);
            actors++;
        }
        items++;
    }
    return count;
}

void move_familiar_prompt_selection(CachedFamiliarPrompt *prompt, s32 index)
{
    if (index != prompt->selected_actor_index && prompt->actor_count != 0) {
        s32 page;

        SD_Call(AUDIO_CURSOR_MOVE);
        prompt->selected_actor_index = index;
        prompt->selected_actor = prompt->actors[index];
        page = prompt->selected_actor_index / 5;
        if (page != prompt->current_page) {
            prompt->current_page = page;
            update_familiar_prompt_page(prompt->parts, prompt);
        } else {
            position_familiar_prompt_cursors(prompt->parts, prompt->selected_actor_index);
        }
        change_status_display_target(get_familiar_prompt_actor_status(prompt->owner),
                                     prompt->selected_actor, 3);
        update_familiar_prompt_description(prompt);
    }
}

void retry_familiar_assignment(CachedFamiliarPrompt *prompt)
{
    if (begin_familiar_assignment(prompt) != 0) {
        NODE_HEADER(prompt)->update_callback = prompt->previous_update;
    }
}

void initialize_familiar_prompt_request(CachedFamiliarPrompt *prompt, ObjectNodeHeader *owner,
                                             ActorRecord *actor)
{
    s32 count;

    prompt->available_slots = get_familiar_menu_state_mask();
    count = collect_familiar_actors(GAME_STATE->item_list, prompt->actors);
    prompt->actor_count = count;
    if (count != 0) {
        prompt->selected_actor_index = find_familiar_prompt_actor(prompt->actors, actor, count);
        prompt->selected_actor = actor;
        prompt->current_page = prompt->selected_actor_index / 5;
        prompt->last_page = (prompt->actor_count - 1) / 5;

    }
    initialize_familiar_cursor_shape(&prompt->packets->cursor);
    build_familiar_backdrop(&prompt->packets->backdrop);
    set_item_panel_height(prompt->packets, 0);
    prompt->assignment_slot = select_familiar_assignment_slot(prompt->actors[prompt->selected_actor_index],
                                                                    0, prompt->available_slots);
    prompt->owner = owner;
    NODE_HEADER(prompt)->update_callback = advance_familiar_prompt_opening;
}

void poll_familiar_prompt_input(CachedFamiliarPrompt *prompt)
{
    GameWork *work = &g_game_work;
    s32 held = work->buttons;
    s32 direction = 0;
    s32 index;

    if (held != 0 && prompt->input_enabled != 0) {
        s32 pressed = work->pressed_buttons;

        if (pressed & 0x20) {
            SD_Call(AUDIO_CANCEL);
            schedule_familiar_prompt_close(prompt->owner);
        } else if (pressed & 0x40) {
            SD_Call(AUDIO_ACCEPT);
            if (prompt->actor_count != 0) {
                if (begin_familiar_assignment(prompt) == 0) {
                    void *previous = NODE_HEADER(prompt)->update_callback;

                    NODE_HEADER(prompt)->update_callback = retry_familiar_assignment;
                    prompt->previous_update = previous;
                }
                disable_familiar_prompt_flow_input(prompt->owner);
            }
        } else if ((held & 0xf000) && prompt->actor_count != 0) {
            s32 slot;

            if (pressed & 0xf000) {
                prompt->repeat_delay = 0;
                pressed = work->pressed_buttons;
                if (pressed & 0x8000) {
                    direction = -5;
                } else if (pressed & 0x2000) {
                    direction = 5;
                } else if (pressed & 0x1000) {
                    direction = -1;
                } else if (pressed & 0x4000) {
                    direction = 1;
                }
            } else if (prompt->repeat_delay >= 9) {
                if (held & 0x8000) {
                    direction = -5;
                } else if (held & 0x2000) {
                    direction = 5;
                } else if (held & 0x1000) {
                    direction = -1;
                } else if (held & 0x4000) {
                    direction = 1;
                }
                prompt->repeat_delay--;
            } else {
                prompt->repeat_delay++;
                return;
            }
            if (direction != 0) {
                index = advance_index_with_directional_clamp(prompt->selected_actor_index, direction,
                                                              prompt->actor_count);
                slot = select_familiar_assignment_slot(prompt->actors[index], prompt->assignment_slot,
                                                              prompt->available_slots);
                shade_familiar_assignment_slots(prompt->parts, slot);
                prompt->assignment_slot = slot;
                move_familiar_prompt_selection(prompt, index);
            }
        } else if (work->pressed_buttons & 3) {
            s32 slot;

            SD_Call(AUDIO_CURSOR_MOVE);
            slot = prompt->assignment_slot;
            if (work->pressed_buttons & 1) {
                if (prompt->available_slots & 2) {
                    slot = 1;
                }
            } else if (prompt->available_slots & 1) {
                slot = 0;
            }
            index = find_familiar_assignment_actor(slot, prompt->selected_actor_index, prompt->actor_count,
                                                          prompt->actors);
            slot = select_familiar_assignment_slot(prompt->actors[index], slot, prompt->available_slots);
            move_familiar_prompt_selection(prompt, index);
            shade_familiar_assignment_slots(prompt->parts, slot);
            prompt->assignment_slot = slot;
        }
    }
    if (test_resident_bitmap_bit(2)) {
        clear_resident_bitmap_bit(2);
        schedule_familiar_prompt_close(prompt->owner);
    }
}

s32 find_familiar_assignment_actor(s32 slot, s32 fallback, s32 count, ActorRecord **actors)
{
    if (get_cached_player_familiar(slot) != 0) {
        s32 index;

        for (index = 0; index < count; index++) {
            if (get_menu_actor_index(actors[index]) == slot) {
                return index;
            }
        }
    }
    return fallback;
}
