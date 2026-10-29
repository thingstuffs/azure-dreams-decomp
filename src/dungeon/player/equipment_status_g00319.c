/* Equipment status (G00319). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:dungeon/engine:800E07C0, PD:dungeon/engine:800E07D3. */
#include "dungeon/player/equipment_status_g00319.h"
#include "dungeon/player/object.h"

/* Changes equipped items unless blocked, displays the result, and updates actor sprites and palettes. */
void equip_item_and_update_status(ActorRecord *context, DungeonItemEntry *item) {
    s32 value;
    register void *result_value;
    s32 item_index;
    s16 tail_index;
    s16 state;
    s32 item_b3;
    u8 *text_end;
    DungeonItemEntry *current_item;
    DungeonItemEntry *selected_item;
    u8 *head_c;
    u8 *head_b;
    u8 head_b_value;

    selected_item = item;
    result_value = 0;
    state = 0;
    if (selected_item != NULL) {
        if (selected_item->kind == 0xF && selected_item->unk_00 >= 0xD) {
            play_sound_if_enabled(0x506);
            result_value = get_unused_text_buffer();
            text_end = append_typed_formatted_value(selected_item, expand_text_control_codes(D_800E080A, append_entity_display_text(context, write_text_byte_and_advance(8, result_value))));
            clear_byte_and_advance(expand_text_control_codes(D_80088B64, text_end));
            display_text_with_fullwidth_adjustment(result_value);
            return;
        }
        selected_item = register_item_object_in_free_slot(selected_item, D_800E07C0, D_800E07D3, 0);
        if (selected_item == NULL) {
            return;
        }
    }

    current_item = context->unk_4C;
    if (current_item != NULL) {
        value = current_item->unk_03;
        if (value & 0x40) {
            play_sound_if_enabled(0x70A);
            result_value = get_unused_text_buffer();
            text_end = append_typed_formatted_value(current_item, write_text_byte_and_advance(8, result_value));
            clear_byte_and_advance(expand_text_control_codes(D_800E081C, text_end));
            display_text_with_fullwidth_adjustment(result_value);
            return;
        }
        current_item->unk_03 = value & 0xDF;
        actor_direction_sprites[0] = (s32 *)unequipped_actor_sprite_sources;
        if (current_item == selected_item) {
            selected_item = NULL;
        }
        state = 1;
    }

    if (selected_item != NULL) {
        item_b3 = selected_item->unk_03;
        item_index = selected_item->unk_00;
        selected_item->unk_03 = item_b3 & 0x7F;
        result_value = get_unused_text_buffer();
        clear_byte_and_advance(expand_text_control_codes(D_800E0844, append_typed_formatted_value(selected_item, write_text_byte_and_advance(8, result_value))));
        display_text_with_fullwidth_adjustment(result_value);
        actor_direction_sprites[0] = (s32 *)equipped_actor_sprite_sources;
        tail_index = 0x70A;
        if (selected_item->unk_03 & 0x40) {
            context->flags1C |= 0x800;
            play_sound_if_enabled(tail_index);
            result_value = get_unused_text_buffer();
            clear_byte_and_advance(expand_text_control_codes(D_800E0853, append_typed_formatted_value(selected_item, result_value)));
            display_text_with_fullwidth_adjustment(result_value);
        }
        selected_item->unk_03 |= 0x20;
    } else {
        if (state != 0) {
            result_value = get_unused_text_buffer();
            text_end = write_text_byte_and_advance(8, result_value);
            text_end = append_typed_formatted_value(context->unk_4C, text_end);
            text_end = expand_text_control_codes(D_800E0862, text_end);
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(result_value);
        }
        head_c = D_800DD2C4;
        context->unk_84 = head_c[0];
        head_b = D_800DD2B4;
        head_b_value = head_b[0];
        item_index = 0;
        context->unk_85 = head_b_value;
    }
    context->unk_4C = selected_item;
    play_sound_if_enabled(0x508);
    tail_index = item_index;
    if (selected_item->kind == 0x10) {
        context->unk_84 = D_800DD2E0[tail_index];
        context->unk_85 = D_800DD2D4[tail_index];
        if (tail_index == 0) {
            clear_alternate_texture_regions(1);
            return;
        }
        load_equipment_palette_for_category_sixteen(tail_index);
    } else {
        context->unk_84 = D_800DD2C4[tail_index];
        context->unk_85 = D_800DD2B4[tail_index];
        if (tail_index == 0) {
            clear_alternate_texture_regions(1);
            return;
        }
        load_default_object_palette(tail_index);
    }
    if (item_index == 0) {
        clear_alternate_texture_regions(1);
    }
}

/* Changes the actor's equipped item and displays status messages. */
void change_equipped_item_and_notify(S_80098614_0 *actor, DungeonItemEntry *requested_item)
{
    DungeonItemEntry *item;
    DungeonItemEntry *equipped_item;
    s32 item_flags;
    s32 item_id;
    s32 had_equipped;
    s32 text_end;
    void *state;
    s16 equipped;

    item = requested_item;
    equipped = 0;

    if (item != 0) {
        item = register_item_object_in_free_slot(item, D_800E07C0, D_800E07D3, 0);
        if (item == 0) {
            return;
        }
    }

    equipped_item = actor->unk_50.p;
    if (equipped_item != 0) {
        item_flags = equipped_item->unk_03;
        if (item_flags & 0x40) {
            play_sound_if_enabled(0x70A);
            state = get_unused_text_buffer();
            text_end = write_text_byte_and_advance(8, state);
            text_end = append_typed_formatted_value((struct DungeonItemEntry *)equipped_item, text_end);
            text_end = expand_text_control_codes(D_800E0874, text_end);
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(state);
            return;
        }
        equipped_item->unk_03 = item_flags & 0xDF;
        if (equipped_item == item) {
            item = 0;
        }
        equipped = 1;
    }

    had_equipped = equipped;
    if (item != 0) {
        item->unk_03 &= 0x7F;
        item_id = item->unk_00;
        state = get_unused_text_buffer();
        text_end = write_text_byte_and_advance(8, state);
        text_end = append_typed_formatted_value((struct DungeonItemEntry *)item, text_end);
        text_end = expand_text_control_codes(D_800E089C, text_end);
        clear_byte_and_advance(text_end);
        display_text_with_fullwidth_adjustment(state);

        if (item->unk_03 & 0x40) {
            actor->unk_1C |= 0x800;
            play_sound_if_enabled(0x70A);
            state = get_unused_text_buffer();
            text_end = append_typed_formatted_value((struct DungeonItemEntry *)item, state);
            text_end = expand_text_control_codes(D_800E08AB, text_end);
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(state);
        }

        item->unk_03 |= 0x20;
    } else {
        item_id = 0;
        if (had_equipped != 0) {
            state = get_unused_text_buffer();
            text_end = write_text_byte_and_advance(8, state);
            text_end = append_typed_formatted_value((struct DungeonItemEntry *)actor->unk_50.p2, text_end);
            text_end = expand_text_control_codes(D_800E08BA, text_end);
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(state);
        }

    }

    actor->unk_50.p = item;
    play_sound_if_enabled(0x508);
    text_end = item_id;
    actor->unk_86 = D_800DD2EC[text_end];
    if (text_end != 0) {
        load_equipment_change_palette(text_end);
        return;
    }
    clear_alternate_texture_regions(0);
}
