#include "engine/util.h"
#include "dungeon/player.h"
#include "town/shop/position.h"
#include "slus.h"
#include "sdk/libc.h"
#include "dungeon/actor.h"
#include "dungeon/menu_cache_stats.h"
#include "engine/effect.h"
#include "engine/text.h"
#include "town/shop/stat_display.h"

/* Append experience markers and restore the default text style. */
char *format_cached_gauge_text(char *output, ActorRecord *actor)
{
    u32 value;
    s32 pair_test;
    s16 count;
    char format_buf[64];
    s16 pair_count;
    s32 pair_index;

    memcpy(output, cached_gauge_prefix, sizeof(Text5));
    strcat(output, uint_to_dec_str(1, format_buf));
    value = calc_gauge_fill(actor);
    count = value;
    pair_test = count / 2;
    pair_index = 0;
    if (pair_test > 0) {
        pair_count = pair_test;
        do {
            strcat(output, cached_full_gauge_marker);
            pair_index++;
        } while (pair_index < pair_count);
    }
    value = count & 1;
    if (value) {
        strcat(output, cached_half_gauge_marker);
    }
    strcat(output, cached_gauge_suffix);
    strcat(output, uint_to_dec_str(0, format_buf));
    return output;
}

/* Format the weapon and shield bonuses as two three-digit fields. */
char *format_cached_equipment_bonuses(char *output, ActorRecord *actor)
{
    char digits[64];
    s16 attack;
    s16 defense;

    memcpy(output, cached_equipment_prefix, 7);
    attack = get_clamped_adjusted_value(actor);
    format_int_space_padded(attack, 3, digits);
    strcat(output, digits);
    strcat(output, cached_equipment_separator);
    defense = get_shield_defense_bonus(actor);
    format_int_space_padded(defense, 3, digits);
    strcat(output, digits);
    return output;
}

/* Show effective attack and defense with indicators for changes from their baselines. */
char *format_cached_attack_defense(char *output, ActorRecord *actor)
{
    char digits[12];
    s32 indicator;
    const char *defense_separator;

    memcpy(output, cached_comparison_prefix, 3);
    indicator = compare_values_to_display_code(actor->base_attack, actor->current_attack);
    if (indicator != 0) {
        strcat(output, cached_comparison_marker_separator);
        strcat(output, uint_to_dec_str(indicator, digits));
    }
    strcat(output, cached_comparison_attack_separator);
    format_int_space_padded(actor->current_attack, 3, digits);
    strcat(output, digits);
    strcat(output, cached_comparison_marker_separator);
    strcat(output, uint_to_dec_str(0, digits));
    indicator = compare_values_to_display_code(actor->base_defense, actor->current_defense);
    if (indicator != 0) {
        strcat(output, cached_comparison_marker_separator);
        strcat(output, uint_to_dec_str(indicator, digits));
    }
    defense_separator = cached_comparison_defense_separator;
    strcat(output, defense_separator);
    format_int_space_padded(actor->current_defense, 3, digits);
    strcat(output, digits);
    strcat(output, cached_comparison_marker_separator);
    strcat(output, uint_to_dec_str(0, digits));
    strcat(output, cached_status_separator);
    strcat(output, cached_comparison_base_separator);
    format_int_space_padded(actor->base_attack, 3, digits);
    strcat(output, digits);
    strcat(output, defense_separator);
    format_int_space_padded(actor->base_defense, 3, digits);
    strcat(output, digits);
    return output;
}

/* Populate the status panel with level, HP and the formatted stat lines. */
void draw_cached_actor_stats(ActorRecord *actor, ItemMenuPart **panels)
{
    char digits[64];
    char text[64];

    memcpy(text, cached_stat_prefix, 5);

    format_int_space_padded(actor->level, 2, digits);
    remap_flagged_string_bytes(digits);
    strcat(text, digits);
    strcat(text, cached_stat_suffix);
    strcat(text, cached_stat_line_break);

    format_int_space_padded(actor->hp, 3, digits);
    strcat(text, digits);
    strcat(text, cached_stat_separator);

    format_int_space_padded(actor->max_hp, 3, digits);
    strcat(text, digits);

    set_storage_entry_text(panels[4], text, 0, 0x6C, 0x98);
    set_storage_entry_text(panels[19], (char *)cached_stat_column_labels, 0, 0x48, 0xB8);
    set_storage_entry_text(panels[5], format_cached_gauge_text(text, actor), 0, 0x48, 0xC8);
    set_storage_entry_text(panels[18], format_cached_attack_defense(text, actor), 0, 0x48, 0xB8);
    set_storage_entry_text(panels[2], format_cached_equipment_bonuses(text, actor), 0, 0x48, 0xB0);
}

/* Draw the party actor version with HP, MP and a species label. */
void draw_party_actor_stats(ActorRecord *actor, ItemMenuPart **panels)
{
    char digits[64];
    char text[64];
    const char *species_name;
    s32 text_style;

    memcpy(text, cached_stat_prefix, 5);

    format_int_space_padded(actor->level, 2, digits);
    remap_flagged_string_bytes(digits);
    strcat(text, digits);
    strcat(text, cached_stat_suffix);
    strcat(text, cached_stat_line_break);

    format_int_space_padded(actor->hp, 3, digits);
    strcat(text, digits);
    strcat(text, cached_stat_separator);

    format_int_space_padded(actor->max_hp, 3, digits);
    strcat(text, digits);
    strcat(text, cached_hp_mp_break);

    format_int_space_padded(actor->mp, 3, digits);
    strcat(text, digits);
    strcat(text, cached_stat_separator);

    format_int_space_padded(actor->max_mp, 3, digits);
    strcat(text, digits);

    set_storage_entry_text(panels[5], text, 0, 0x6C, 0x98);
    species_name = (const char *)(unsigned long)(u32)monster_get_species_name_text(normalize_monster_status_species_code(actor->species));
    text_style = 0;
    if (actor->town_monster_slot >= 0x41) {
        text_style = 3;
    }
    /* The text setter receives the string address as a word. */
    set_display_entry_text_and_position(panels[6], (s32)(unsigned long)species_name, text_style, 0x68, 0x98);
    set_storage_entry_text(panels[7], format_cached_gauge_text(text, actor), 0, 0x48, 0xC8);
    set_storage_entry_text(panels[19], (char *)cached_stat_column_labels, 0, 0x48, 0xB8);
    set_storage_entry_text(panels[18], format_cached_attack_defense(text, actor), 0, 0x48, 0xB8);
}
