#include "shared/actor_property_flags.h"
#include "dungeon/player.h"
#include "shared/monster_ids.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
/* Complete native TU in retail file order. Review pending. */
#include "dungeon/player/object/can_entity_gain_level.h"
#include "dungeon/player/object/action_state.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/player/object.h"
#define F(p,t,o) (*(t *)((u8 *)(p) + (o)))
extern s32 get_entity_effect_value(void *entry, s32 effect_id);
extern s32 entity_level_thresholds[];
extern u8 D_800E0000[];
/* Checks whether an entity can level up with its current experience. */
s32 can_entity_gain_level(void *entity) {
    s16 can_level_up = 0;
    s32 *exp_table;
    u8 *exp_entry;
    u8 level;
    u16 table_offset;

    if (F(entity, s8, 0x13) < 0) {
        return 0;
    }
    /*
     * Original bug: Salamanders can qualify for level-up after their last attack disables the callback that clears
     * their EXP. An off-screen kill can then make the pending EXP owner block its own removal.
     * Found and documented by the Azure Dreams community
     * (adrando.com/guide/bugs.html).
     */
    if (F(entity, u8, 0x11) >= 0x63) {
        return 0;
    }
    if ((get_entity_effect_value(entity,  STATUS_FROG) << 16) != 0) {
        return 0;
    }
    if (F(entity, u32, 0x1C) & ACTOR_LIFTED) {
        return can_level_up;
    }
    if (F(entity, u8, 0x13) == 0) {
                 /* Required for byte-exact code generation. */
        if (F(F(D_800E0000, u8 *, 0x3D7C), u8, 0x9A) == 0x22) {
            return can_level_up;
        }
    }
    if (F(entity, u32, 0x1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
        return can_level_up;
    }
         /* Required for byte-exact code generation. */
    level = F(entity, u8, 0x11);
    table_offset = level << 2;
    exp_table = (s32 *)entity_level_thresholds;
    exp_entry = (u8 *)(table_offset + (u32)exp_table);
         /* Required for byte-exact code generation. */
    if (*(u32 *)exp_entry <= F(entity, u32, 0x18)) {
        can_level_up++;
    }
    return can_level_up;
}
#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

extern s32 format_unsigned_double_byte_decimal();
extern s32 apply_entity_effects();
extern s32 SquareRoot12();
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes();
extern s32 copy_four_text_bytes();
extern void * clear_byte_and_advance(s8 *byte_ptr);
extern s32 write_text_byte_and_advance();
extern s32 append_entity_display_text();
extern s32 display_text_with_fullwidth_adjustment();
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);

extern u8 species_base_stats[];
extern u8 species_growth_table[];
extern u8 D_800E0953[];
extern u8 D_800E095F[];
extern u8 D_800E0970[];
extern u8 D_800E0979[];

/* Raise the entity one level, update its stats, XP reward and abilities, and optionally display a message. */
s32 raise_entity_level(void *entity_data, s32 show_message) {
    u8 ability_gained[3];
    u8 *stat_growth;
    u8 *initial_stats;
    s32 level;
    s32 prev_level;
    s32 species_id;
    s32 slot;
    s32 message;
    s32 text_end;
    s32 old_stat;
    s32 level_product;
    s32 level_product_2;

    if (((u8 *)entity_data)[0x11] < 99U) {
        s32 stat_gain_m;
        level = ((u8 *)entity_data)[0x11];
        species_id = ((u8 *)entity_data)[0x13];
        ((u8 *)entity_data)[0x11] = level + 1;
        stat_growth = species_growth_table + (species_id * 8);
        prev_level = level - 1;
        initial_stats = species_base_stats + (species_id * 0x18);

        {
            s32 old_base;
            s32 curve_value;
            s32 old_linear;
            s32 old_curve;
            s32 new_linear;
            s32 new_curve;
            s32 new_sum;
            s32 new_base;
            s32 new_stat;
            s32 old_sum;
            s32 stat;
            s32 old_value;
            curve_value = SquareRoot12((prev_level * stat_growth[5]) << 0xB);
            old_base = initial_stats[5];
            old_linear = stat_growth[5] * prev_level;
            if (old_linear < 0) {
                old_linear += 0xF;
            }
            old_curve = stat_growth[5] * curve_value;
            old_sum = old_base + (old_linear >> 4);
            old_stat = old_sum + (old_curve / 32768);

            level_product = level * stat_growth[5];
            curve_value = SquareRoot12(level_product << 0xB);
            new_base = *(u8 *)(initial_stats + 5);
            new_linear = stat_growth[5] * level;
            if (new_linear < 0) {
                new_linear += 0xF;
            }
            new_curve = stat_growth[5] * curve_value;
            new_sum = new_base + (new_linear >> 4);
            if (new_curve < 0) {
                new_curve += 0x7FFF;
                new_stat = new_sum + (new_curve >> 0xF);
            } else {
                new_stat = new_sum + (new_curve >> 0xF);
            }

            stat = ((u8 *)entity_data)[5];
            old_value = stat;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[5] = stat;
            /*
             * Original bug: HP growth is added directly to a byte even when doubled HP is already 255. It wraps instead
             * of saturating; a full-health Naplass can reach zero HP on leveling up.
             */
            ((u8 *)entity_data)[0x28] += stat_gain_m;
        }

        {
            s32 old_scaled;
            s32 new_scaled;
            s32 new_stat;
            s32 stat;
            s32 old_value;
            {
                s32 base_stat;
                old_scaled = stat_growth[4];
                base_stat = initial_stats[4];
                slot = old_scaled * base_stat;
                old_scaled = slot * prev_level;
            }
            if (old_scaled < 0) {
                old_scaled += 0x3FF;
            }
            new_scaled = slot * level;
            old_stat = initial_stats[4] + (old_scaled >> 0xA);
            new_stat = initial_stats[4] + (new_scaled / 1024);
            stat = ((u8 *)entity_data)[4];
            old_value = stat;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[4] = stat;
            ((u8 *)entity_data)[0x25] += stat_gain_m;
        }

        {
            s32 base_stat;
            s32 old_scaled;
            s32 new_stat;
            s32 stat;
            s32 old_value;
            old_scaled = stat_growth[0];
            base_stat = initial_stats[0];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_level;
            stat = ((u8 *)entity_data)[0];
            old_value = stat;
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            stat_gain_m = slot * level;
            old_stat = initial_stats[0] + (old_scaled >> 6);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3F;
            }
            new_stat = initial_stats[0] + (stat_gain_m >> 6);
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[0] = stat;
            /*
             * Original bug: doubled attack can already be 255 while base attack still grows. This byte addition wraps;
             * a full-strength Arachne can reach zero attack on leveling up.
             */
            ((u8 *)entity_data)[0x26] += stat_gain_m;
        }

        {
            s32 prev_step;
            s32 base_stat;
            s32 old_scaled;
            s32 new_stat;
            s32 stat;
            s32 old_value;
            prev_step = level - 1;

            old_scaled = stat_growth[1];
            base_stat = initial_stats[1];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[1];
            old_value = stat;
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 6);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3F;
            }
            old_scaled = stat_gain_m >> 6;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            stat_gain_m = stat - old_value;
            ((u8 *)entity_data)[1] = stat;
            /*
             * Original bug: doubled defense can already be 255 while base defense still grows. This byte addition
             * wraps; a full-strength Metal can drop to 1 defense on leveling up.
             */
            ((u8 *)entity_data)[0x27] += stat_gain_m;

            old_scaled = stat_growth[2];
            base_stat = initial_stats[2];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[2];
            if (old_scaled < 0) {
                old_scaled += 0x3F;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 6);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3F;
            }
            old_scaled = stat_gain_m >> 6;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            ((u8 *)entity_data)[2] = stat;

            old_scaled = stat_growth[3];
            base_stat = initial_stats[3];
            slot = old_scaled * base_stat;
            old_scaled = slot * prev_step;
            stat = ((u8 *)entity_data)[3];
            if (old_scaled < 0) {
                old_scaled += 0x3FF;
            }
            stat_gain_m = slot * level;
            old_stat = base_stat + (old_scaled >> 0xA);
            if (stat_gain_m < 0) {
                stat_gain_m += 0x3FF;
            }
            old_scaled = stat_gain_m >> 0xA;
            new_stat = base_stat + old_scaled;
            stat += new_stat - old_stat;
            if ((u32) stat >= 0x100) {
                stat = 0xFF;
            }
            ((u8 *)entity_data)[3] = stat;
        }

        {
            s16 base_xp;
            u32 linear_word;
            s32 word_growth;
            s32 xp_sum;
            s32 growth_product;
            u32 xp_given;

            base_xp = *(s16 *)(initial_stats + 6);
            linear_word = level * base_xp;
            word_growth = stat_growth[6] * level;
            level_product_2 = level * level;
            xp_sum = base_xp + word_growth;
            growth_product = level_product_2 * xp_sum;
            xp_given = base_xp + linear_word;
            xp_given += (growth_product / 512);
            if (xp_given > 0xFFFFU) {
                xp_given = 0xFFFF;
            }
            *(u16 *)(((u8 *)entity_data) + 6) = xp_given;
        }

        if (((u8 *)entity_data)[0x13] != 0) {
            u8 *gained_base;
            s32 gained_flag;
            u8 *ability_table;
            s32 levels_left;
            u8 *ability_slot;
            u8 *gained;
            s32 ability_value;

            slot = 2;
            gained_base = ability_gained;
            ability_table = item_action_definitions;
            gained_flag = 1;
            levels_left = 100 - level;
            ability_slot = ((u8 *)entity_data) + 6;
loop_0:
            {
                gained = gained_base + slot;
                *gained = 0;
                ability_value = ability_slot[8];
                if (ability_value != 0) {
                    s32 type_mask = ability_table[ability_value * 0x14 + 0x10] >> 4;
                    if ((type_mask & (*(s32 *)(((u8 *)entity_data) + 0x14))) || !(type_mask & 7)) {
                        s32 ability_level = ability_slot[10];
                        if ((u32) ability_level < 99U) {
                            s32 new_level;
                            s32 level_bonus;
                            ability_slot[10] = ability_level + 1;
                            *gained = gained_flag;
                            ability_value = ability_slot[10];
                            level_bonus = 99;
                            level_bonus = level_bonus - ability_value;
                            level_bonus = level_bonus / levels_left;
                            new_level = level_bonus + ability_value;
                            if (new_level >= 100) {
                                new_level = 99;
                            }
                            ability_slot[10] = new_level;
                        }
                    }
                }
                slot -= 1;
                ability_slot -= 3;
            }
            if (slot >= 0)
                goto loop_0;
        }

        apply_entity_effects(((u8 *)entity_data));

        if ((show_message << 0x10) != 0) {
            if (!(system_update_flags & 1)) {
                dungeon_event_pending_flag[0] = 1;
                g_dungeon_status.activity_counts.parts.pending_action_count++;
            }
            stat_gain_m = 0x8003;
            if ((*(s32 *)(((u8 *)entity_data) + 0x14) & 0x2000) != 0) {
                stat_gain_m = 0x8002;
            }
            create_actor_value_popup(stat_gain_m, ((u8 *)entity_data), -2, 1);

            message = get_unused_text_buffer();
            text_end = expand_text_control_codes(D_800E0953, message);
            text_end = write_text_byte_and_advance(0xA, text_end);
            text_end = append_entity_display_text(((u8 *)entity_data), text_end);
            text_end = expand_text_control_codes(D_800E095F, text_end);
            text_end = format_unsigned_double_byte_decimal(((u8 *)entity_data)[0x11], text_end);
            text_end = expand_text_control_codes(fullwidth_period, text_end);

            if (((u8 *)entity_data)[0x13] != 0 && ((*(s32 *)(((u8 *)entity_data) + 0x14) & 0x4000) != 0)) {
                u8 *ability_slot;
                u8 *ability_table;
                slot = 0;
                ability_table = item_action_definitions;
                ability_slot = ((u8 *)entity_data);
                do {
                    if (ability_gained[slot] != 0) {
                        text_end = write_text_byte_and_advance(0xA, text_end);
                        text_end = expand_text_control_codes(*(s32 *)(ability_table + ability_slot[8] * 0x14), text_end);
                        text_end = expand_text_control_codes(D_800E0970, text_end);
                        text_end = expand_text_control_codes(D_800E0979, text_end);
                    }
                    slot += 1;
                    ability_slot += 3;
                } while (slot < 3);
            }

            if (!(system_update_flags & 1)) {
                text_end = write_text_byte_and_advance(0x11, text_end);
                text_end = write_text_byte_and_advance(0x4C, text_end);
                text_end = copy_four_text_bytes(familiar_defeat_text, text_end);
            }
            clear_byte_and_advance(text_end);
            display_text_with_fullwidth_adjustment(message);
        }
    }
}
#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_status.h"

#include "m2c_compat.h"

extern s32 format_unsigned_double_byte_decimal();
extern s32 apply_entity_effects();
extern s32 SquareRoot12();
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes();
extern s32 copy_four_text_bytes();
extern void * clear_byte_and_advance(s8 *byte_ptr);
extern s32 write_text_byte_and_advance();
extern s32 append_entity_display_text();
extern s32 play_sound_if_enabled();
extern s32 display_text_with_fullwidth_adjustment();
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);

extern u8 species_base_stats[];
extern s32 entity_level_thresholds[];
extern u8 species_growth_table[];
extern u8 D_800E098B[15];
extern u8 D_800E099A[24];
extern u8 D_800E09B2[9];
extern u8 D_800E09BB[18];

/* Lower an entity by one level, adjust its stats and spells, and optionally show a message. */
s32 lower_entity_level(void *entity_data, s32 show_message) {
    u8 spell_lowered[3];
    u8 *entity;
    u8 *stat_growth;
    u8 *initial_stats;
    s32 level;
    s32 level_offset;
    s32 monster_id;
    s32 spell_index;
    s32 message_start;
    s32 message_end;
    s32 lower_stat;
    s32 temp;
    s32 level_term_2;
    s32 *xp_table;

    entity = (u8 *)entity_data;
    if (entity[0x11] < 2U) {
        return 0;
    }
    /*
     * Original bug: level loss subtracts the evolved species' growth from inherited stats but only repairs exactly
     * zero. Negative results wrap to 255; clamp them before byte stores.
     * Found and documented by the Azure Dreams community
     * (adrando.com/guide/bugs.html).
     */
    entity[0x11] -= 1;
    level = entity[0x11];
    monster_id = entity[0x13];
    xp_table = entity_level_thresholds;
    *(s32 *)(entity + 0x18) = xp_table[level] - 1;
    stat_growth = species_growth_table + (monster_id * 8);
    level_offset = level - 1;
    initial_stats = species_base_stats + (monster_id * 0x18);

    {
        s32 base_hp;
        s32 hp_curve;
        s32 lower_hp_growth;
        s32 lower_hp_curve;
        s32 upper_hp_growth;
        s32 upper_hp_curve;

        s32 upper_stat;
        s32 lower_hp_base;
        s32 stat_value;
        hp_curve = SquareRoot12((level_offset * stat_growth[5]) << 0xB);
        base_hp = *(u8 *)(initial_stats + 5);
        temp = stat_growth[5];
        lower_hp_growth = temp * level_offset;
        if (lower_hp_growth < 0) {
            lower_hp_growth += 0xF;
        }
        lower_hp_curve = temp * hp_curve;
        lower_hp_base = base_hp + (lower_hp_growth >> 4);
        if (lower_hp_curve < 0) {
            lower_hp_curve += 0x7FFF;
        }
        lower_stat = lower_hp_base + (lower_hp_curve >> 0xF);

        hp_curve = SquareRoot12((level * temp) << 0xB);
        lower_hp_curve = *(u8 *)(initial_stats + 5);
        upper_hp_growth = stat_growth[5] * level;
        if (upper_hp_growth < 0) {
            upper_hp_growth += 0xF;
        }
        upper_hp_curve = stat_growth[5] * hp_curve;
        upper_hp_growth = lower_hp_curve + (upper_hp_growth >> 4);
        upper_stat = upper_hp_growth + (upper_hp_curve / 32768);

        stat_value = entity[5] + (lower_stat - upper_stat);
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[5] = stat_value;
    }

    {
        s32 lower_growth;
        s32 upper_stat;
        s32 stat_value;
        {
            s32 base_stat;
            lower_growth = stat_growth[4];
            base_stat = initial_stats[4];
            lower_stat = lower_growth * base_stat;
            lower_growth = lower_stat * level_offset;
        }
        if (lower_growth < 0) {
            lower_growth += 0x3FF;
        }
        stat_value = lower_stat * level;
        lower_stat = initial_stats[4] + (lower_growth >> 0xA);
        if (stat_value < 0) {
            stat_value += 0x3FF;
        }
        upper_stat = initial_stats[4] + (stat_value >> 0xA);
        stat_value = entity[4] + (lower_stat - upper_stat);
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[4] = stat_value;
    }

    {
        s32 base_stat;
        s32 lower_growth;
        s32 upper_stat;
        s32 stat_value;
        lower_growth = stat_growth[0];
        base_stat = initial_stats[0];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * level_offset;
        stat_value = entity[0];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        temp = spell_index * level;
        lower_stat = initial_stats[0] + (lower_growth >> 6);
        if (temp < 0) {
            temp += 0x3F;
        }
        upper_stat = initial_stats[0] + (temp >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[0] = stat_value;
    }

    {
        s32 stat_level_offset;
        s32 base_stat;
        s32 lower_growth;
        s32 upper_stat;
        s32 stat_value;
        stat_level_offset = level - 1;
        lower_growth = stat_growth[1];
        base_stat = initial_stats[1];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[1];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        temp = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 6);
        if (temp < 0) {
            temp += 0x3F;
        }
        upper_stat = base_stat + (temp >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[1] = stat_value;

        lower_growth = stat_growth[2];
        base_stat = initial_stats[2];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[2];
        if (lower_growth < 0) {
            lower_growth += 0x3F;
        }
        temp = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 6);
        if (temp < 0) {
            temp += 0x3F;
        }
        upper_stat = base_stat + (temp >> 6);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[2] = stat_value;

        lower_growth = stat_growth[3];
        base_stat = initial_stats[3];
        spell_index = lower_growth * base_stat;
        lower_growth = spell_index * stat_level_offset;
        stat_value = entity[3];
        if (lower_growth < 0) {
            lower_growth += 0x3FF;
        }
        temp = spell_index * level;
        lower_stat = base_stat + (lower_growth >> 0xA);
        if (temp < 0) {
            temp += 0x3FF;
        }
        upper_stat = base_stat + (temp >> 0xA);
        stat_value += lower_stat - upper_stat;
        if (stat_value == 0) {
            stat_value = 1;
        }
        entity[3] = stat_value;
    }

    {
        s16 base_xp;
        s32 linear_xp;
        u32 xp_growth;
        s32 xp_factor;
        s32 growth_product;
        u32 xp_given;

        base_xp = *(s16 *)(initial_stats + 6);
        linear_xp = level * base_xp;
        xp_growth = stat_growth[6] * level;
        level_term_2 = level * level;
        xp_factor = base_xp + xp_growth;
        growth_product = level_term_2 * xp_factor;
        xp_given = base_xp + linear_xp;
        xp_given += (growth_product / 512);
        if (xp_given > 0xFFFFU) {
            xp_given = 0xFFFF;
        }
        *(u16 *)(entity + 6) = xp_given;
    }

    if (entity[0x13] != 0) {
        spell_index = 2;
        {
            u8 *spell_flags;
            u8 *spell_table;
            u8 *lowered_flag;
            s32 lowered_value;
            spell_flags = spell_lowered;
            spell_table = item_action_definitions;
            lowered_value = 1;
            do {
                lowered_flag = spell_flags + spell_index;
                *lowered_flag = 0;
                temp = entity[spell_index * 3 + 8];
                if (temp != 0 && (((spell_table[temp * 0x14 + 0x10] >> 4) & (*(s32 *)(entity + 0x14))) != 0)) {
                    u8 spell_level = entity[spell_index * 3 + 10];
                    if (spell_level >= 2U) {
                        entity[spell_index * 3 + 10] = spell_level - 1;
                        *lowered_flag = lowered_value;
                    }
                }
                spell_index -= 1;
            } while (spell_index >= 0);
        }
    }

    apply_entity_effects(entity);

    if (entity[0x29] < entity[0x28]) {
        entity[0x28] = entity[0x29];
    }
    if (entity[0x66] < entity[0x25]) {
        entity[0x25] = entity[0x66];
        entity[0x24] = (u8)0xFF;
    }
    if (entity[0x68] < entity[0x26]) {
        entity[0x26] = entity[0x68];
    }
    if (entity[0x69] < entity[0x27]) {
        entity[0x27] = entity[0x69];
    }

    if ((show_message << 0x10) == 0) {
        return 1;
    }
    {
        if (!(*(u16 *)0x80013714 & 1)) {
            dungeon_event_pending_flag[0] = 1;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
        }
        create_actor_value_popup(0x8003, entity, -3, 1);
        play_sound_if_enabled(0x615);

        message_start = get_unused_text_buffer();
        message_end = expand_text_control_codes(D_800E098B, message_start);
        message_end = write_text_byte_and_advance(0xA, message_end);
        message_end = append_entity_display_text(entity, message_end);
        message_end = expand_text_control_codes(D_800E099A, message_end);
        message_end = format_unsigned_double_byte_decimal(entity[0x11], message_end);
        message_end = expand_text_control_codes(fullwidth_period, message_end);

        if (entity[0x13] != 0 && ((*(s32 *)(entity + 0x14) & 0x4000) != 0)) {
            spell_index = 0;
            do {
                if (spell_lowered[spell_index] != 0) {
                    message_end = write_text_byte_and_advance(0xA, message_end);
                    message_end = expand_text_control_codes(*(s32 *)(((u8 *)item_action_definitions) + entity[8] * 0x14), message_end);
                    message_end = expand_text_control_codes(D_800E09B2, message_end);
                    message_end = expand_text_control_codes(D_800E09BB, message_end);
                }
                entity += 3;
            } while (++spell_index < 3);
        }

        if (!(system_update_flags & 1)) {
            message_end = write_text_byte_and_advance(0x11, message_end);
            message_end = write_text_byte_and_advance(0x4C, message_end);
            message_end = copy_four_text_bytes(&familiar_defeat_text, message_end);
        }
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
    }
    return 1;
}
#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/dungeon_status.h"

/* Clears dungeon_event_pending_flag and decrements the pending action count. */
void clear_counted_action(void) {

    dungeon_event_pending_flag[0] = 0;
    g_dungeon_status.activity_counts.parts.pending_action_count--;
}
#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* Store tile coordinates as centered positions in 64-unit tiles. */
void set_record_integer_tile_center(ObjectPosition *record, s32 tile_x, s32 tile_y) {
    record->x.w.i = (s16) (((s32) (tile_x << 0x10) >> 0xA) + 0x20);
    record->y.w.i = (s16) (((s32) (tile_y << 0x10) >> 0xA) + 0x20);
}
#include "modules/dungeon_engine_experience_fragment_bc5ec.h"
#include "common.h"
#include "shared/sys_flags.h"

extern u8 camera_transition_timer;

/* Returns one while camera_transition_timer is active and system_update_flags bit 1 is clear. */
s32 is_dungeon_action_blocked(void) {
    if (!(system_update_flags & 2) && camera_transition_timer) {
        return 1;
    }
    return 0;
}
#include "common.h"
#include "shared/dungeon_status.h"

extern s32 is_dungeon_action_blocked(void);

/* Sets or reuses the requested value and calls is_dungeon_action_enabled when state permits. */
s16 try_claim_dungeon_action_slot(s32 requested_value) {
    s32 current_value = ((s32)g_dungeon_status.active_actor);

    if (current_value != requested_value) {
        if (current_value != 0) {
            return 1;
        }
        if (((s32)g_dungeon_status.pending_display_owner) != 0) {
            return 1;
        }
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return 1;
        }
        if (g_dungeon_status.flags & 8) {
            return 1;
        }
        g_dungeon_status.active_actor = requested_value;
    }
    return is_dungeon_action_blocked();
}
#include "common.h"
#include "shared/dungeon_status.h"

/* Return whether any checked global state value or flag is set. */
s32 has_pending_dungeon_activity(void *unused_actor) {
    if (g_dungeon_status.active_actor != 0 ||
        g_dungeon_status.pending_display_owner != 0 ||
        *(s32 *)&g_dungeon_status.activity_counts.word != 0 ||
        (g_dungeon_status.flags & 0x2008) != 0) {
        return 1;
    }
    return 0;
}
#include "common.h"
#include "shared/dungeon_status.h"

/* Returns whether any of the state fields at offsets 0x0A, 0x0C, and 0x10 is nonzero. */
s32 has_pending_actor_or_turn_action(void *unused_actor) {

    if (g_dungeon_status.active_actor != 0 || g_dungeon_status.pending_display_owner != 0 || g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
        return 1;
    }
    return 0;
}
#include "common.h"
#include "shared/dungeon_status.h"

/* Returns whether either state field at offset 0x0A or 0x0C is nonzero. */
s32 has_actor_or_actions(void *unused_actor) {
    s32 has_value;

    has_value = 0;
    if ((g_dungeon_status.active_actor != 0) || (g_dungeon_status.activity_counts.parts.pending_action_count != 0)) {
        has_value = 1;
    }
    return has_value;
}
#include "common.h"
#include "m2c_compat.h"

/* Checks whether the record's byte at offset 0x25 is below 0x40. */
s32 has_low_actor_mp(ActorRecord *record) {
    return (u8) record->mp < 0x40U;
}
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 get_entity_effect_value(void *entry, s32 effect_id);

typedef struct S_800A2CB8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_800A2CB8_1;   /* arg1 in check_entity_interaction_compatibility */

/* Checks entity status and shared flags against another entity. */
u32 check_entity_interaction_compatibility(void *entity, S_800A2CB8_1 *other_entity) {
    if (other_entity == NULL) {
        return 0;
    }
    if (((u32)((ActorRecord *)entity)->flags1C) & (ACTOR_BLIND | ACTOR_CONFUSED)) {
        return 1;
    }
    if (((ActorRecord *)entity)->species == MONSTER_TYRANT &&
        (((ActorRecord *)entity)->action_state_flags & 0x8000)) {
        return 1;
    }
    if ((other_entity->unk_14 & 0x4000) &&
        (((u32)((ActorRecord *)entity)->flags14) & ACTOR_PARTY_MEMBER)) {
        return ((u16)get_entity_effect_value(entity, STATUS_BRAINWASH) << 16) != 0;
    }
    return (((((u32)((ActorRecord *)entity)->flags1C) ^
              other_entity->unk_1C) & 0x2000) << 16) >> 16;
}
#include "common.h"
#include "shared/dungeon_floor.h"

/* Adds to the big-endian value at offset 0x41, saturates at 0xFFFF, and sets the update flag. */
void accumulate_experience_award(u8 *record, u16 amount)
{
    u32 value;

    value = (record[0x41] << 8) | record[0x42];
    value += amount;
    if (value > 0xFFFF) {
        value = 0xFFFF;
    }
    record[0x41] = value >> 8;
    record[0x42] = value;
    dungeon_floor_flags |= 0x100000;
}
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);

typedef struct S_800A2DB8_0 {
    u8 pad_00[0x6];
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    u8 pad_08[0x9];
    u8 unk_11;
    u8 pad_12[0x42];
    s32 unk_54;
    u8 pad_58[0x8];
    void * unk_60;
} S_800A2DB8_0;   /* arg0 in distribute_experience_awards */

typedef struct S_800A2DB8_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x40];
    s32 unk_54;
} S_800A2DB8_1;   /* initial_target in distribute_experience_awards */

typedef struct S_800A2DB8_2 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_2;   /* slot in distribute_experience_awards */

typedef struct S_800A2DB8_3 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_3;   /* member in distribute_experience_awards */

typedef struct S_800A2DB8_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_800A2DB8_5;   /* (u8 *)D_800E3D7C[0] + index * 4 in distribute_experience_awards */

typedef struct S_800A2DB8_6 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800A2DB8_6;   /* global_page in distribute_experience_awards */

typedef struct S_800A2DB8_7 {
    u8 pad_00[0x11];
    u8 unk_11;
    u8 pad_12[0x16];
    u8 unk_28;
} S_800A2DB8_7;   /* global_member in distribute_experience_awards */

/* Award experience to the target or its party and display experience popups. */
s32 distribute_experience_awards(S_800A2DB8_0 *source)
{
    void *initial_target;
    EntityRec *target;
    EntityRec *final_target;
    S_800A2DB8_7 *global_member;
    S_800A2DB8_3 *member;
    u8 *member_slot;
    u8 *global_page;
    s32 recipient_count;
    s32 member_index;
    s32 level_delta;
    s32 award;
    s32 rounded_exp;
    s32 popup_code;
    s32 experience;
    s32 bonus_shift;

    initial_target = source->unk_60;
    experience = 0;
    if (initial_target == NULL) {
        return experience;
    }
    if (((S_800A2DB8_1 *)initial_target)->unk_13 >= 0) {
        experience = source->unk_06.u;
        if (((S_800A2DB8_1 *)initial_target)->unk_54 & 0x20) {
            experience *= 2;
        }

        if (source->unk_54 & 0x40) {
            experience *= 2;
            recipient_count = 1;
        } else {
            recipient_count = 1;
        }

        member_index = recipient_count;
        member_slot = (u8 *)dungeon_actor_ring_anchor + 4;
        do {
            member = ((S_800A2DB8_2 *)member_slot)->unk_AC;
            if ((member != NULL) && (member->unk_28 != 0)) {
                recipient_count++;
            }
            member_index--;
            member_slot -= 4;
        } while (member_index >= 0);

        rounded_exp = experience + recipient_count;
        target = source->unk_60;
        experience = (rounded_exp - 1) / recipient_count;

        if (target->flags14 & ACTOR_PARTY_MEMBER) {
            member_index = 1;
            do {
                member = ((S_800A2DB8_5 *)((u8 *)dungeon_actor_ring_anchor + member_index * 4))->unk_AC;
                if ((member != NULL) && (member->unk_28 != 0)) {
                    level_delta = member->unk_11 - source->unk_11;
                    award = experience;
                    if (level_delta < 0) {
                        /*
                         * Possible original bug: level_delta is already negative, so '< 2' always gives shift zero and
                         * doubles XP. The apparent half-bonus tier for a small level gap is unreachable.
                         */
                        bonus_shift = (level_delta < 2) ^ 1;
                        award = experience + (experience >> bonus_shift);
                    }
                    create_actor_value_popup(0x82, member, (s16)award, 1);
                    /*
                     * Original bug: masking the award to 16 bits wraps EXP above 65535 before the accumulator can
                     * saturate it. Clamp the wide award first.
                     * Found and documented by the Azure Dreams community
                     * (adrando.com/guide/bugs.html).
                     */
                    accumulate_experience_award(member, award & 0xFFFF);
                }
                member_index--;
            } while (member_index >= 0);

            global_page = (u8 *)0x800E0000;
            global_member = ((S_800A2DB8_6 *)global_page)->unk_3D7C;
            if (global_member->unk_28 == 0) {
                return 0;
            }
            level_delta = global_member->unk_11 - source->unk_11;
            award = experience;
            if (level_delta < 0) {
                /*
                 * Possible original bug: level_delta is already negative, so '< 2' always gives shift zero and doubles
                 * XP. The apparent half-bonus tier for a small level gap is unreachable.
                 */
                bonus_shift = (level_delta < 2) ^ 1;
                award = experience + (experience >> bonus_shift);
            }
            /*
             * Original bug: masking the award to 16 bits wraps EXP above 65535 before the accumulator can saturate it.
             * Clamp the wide award first.
             * Found and documented by the Azure Dreams community
             * (adrando.com/guide/bugs.html).
             */
            accumulate_experience_award(global_member, award & 0xFFFF);
            create_actor_value_popup(0x82, ((S_800A2DB8_6 *)global_page)->unk_3D7C, (s16)award, 1);
            return award;
        }

        experience = source->unk_06.u;
        accumulate_experience_award(target, experience);
        final_target = source->unk_60;
        popup_code = 0x83;
        if (final_target->flags14 & ACTOR_CLASS_ENABLED) {
            popup_code = 0x82;
        }
        create_actor_value_popup(popup_code, final_target, source->unk_06.s, 1);
    }
    return experience;
}
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

s32 format_unsigned_double_byte_decimal();                        /* extern */
s32 get_unused_text_buffer();                                /* extern */
s32 expand_text_control_codes();                  /* extern */
extern void * clear_byte_and_advance(s8 *byte_ptr);
s32 append_entity_display_text();                     /* extern */
s32 distribute_experience_awards();                          /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
extern void *monster_species_table;

extern u8 D_800E09CD[12];
extern u8 D_800E09D9[13];
extern u8 D_800E09E6[8];
extern u8 D_800E09EE[13];
extern u8 D_800E09FB[8];

typedef struct S_800A2FE0_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800A2FE0_2;   /* targetState in distribute_experience_and_report_gains */

typedef struct S_800A2FE0_3 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
} S_800A2FE0_3;   /* targetData in distribute_experience_and_report_gains */

typedef struct S_800A2FE0_4 {
    u8 pad_00[0x4];
    s32 * unk_04;
} S_800A2FE0_4;   /* globalData in distribute_experience_and_report_gains */

/* Awards experience when source and target flags permit it and displays the defeat and experience
   messages. */
void distribute_experience_and_report_gains(EntityRec *entity) {
    s32 selectionInputSecond;
    s32 currentValue;
    s32 selectionInputThird;
    s32 flagBits;
    s32 flags14;
    s32 result;
    s32 hasFlag;
    S_800A2FE0_4 *globalData;
    EntityRec *targetEntity;
    S_800A2FE0_2 *targetState;
    S_800A2FE0_3 *targetData;

    result = 0;
    targetEntity = entity->target;
    hasFlag = 0;
    if ((targetEntity != NULL) && (targetEntity->flags14 & ACTOR_PARTY_MEMBER)) {
        flagBits = entity->flags14 & ACTOR_PARTY_MEMBER;
        hasFlag = flagBits != 0;
    }
    if (hasFlag == 0) {
        result = distribute_experience_awards(entity);
    }
    flags14 = entity->flags14;
    if (!(flags14 & 0x20000000)) {
        if (!(flags14 & ACTOR_PARTY_MEMBER)) {
            targetState = entity->target;
            if ((targetState != NULL) && (targetState->unk_13 >= 0)) {
                currentValue = get_unused_text_buffer();
                clear_byte_and_advance(expand_text_control_codes(fullwidth_period, append_entity_display_text(entity, expand_text_control_codes(D_800E09CD, currentValue))));
                display_text_with_fullwidth_adjustment(currentValue);
            }
        }
        if ((result != 0) && (targetData = entity->target, (targetData != NULL))) {
            if (targetData->unk_14 & ACTOR_PARTY_MEMBER) {
                if (!(entity->flags14 & ACTOR_PARTY_MEMBER)) {
                    selectionInputThird = get_unused_text_buffer();
                    globalData = monster_species_table;
                    currentValue = selectionInputThird;
                    clear_byte_and_advance(expand_text_control_codes(D_800E09E6, format_unsigned_double_byte_decimal(result, expand_text_control_codes(D_800E09D9,
                        expand_text_control_codes(globalData->unk_04, currentValue)))));
                } else {
                    return;
                }
            } else {
                if (targetData->unk_13 < 0) {
                    return;
                }
                selectionInputSecond = get_unused_text_buffer();
                currentValue = selectionInputSecond;
                clear_byte_and_advance(expand_text_control_codes(D_800E09FB, format_unsigned_double_byte_decimal(result, expand_text_control_codes(D_800E09EE,
                    append_entity_display_text(entity->target, currentValue)))));
            }
            display_text_with_fullwidth_adjustment(currentValue);
        }
    }
}

/* MECHANISM: The seed's 0x20 frame, s1/s2/s0 roles, CFG, and 124-word shape were already exact.
   The middle get_unused_text_buffer result stays guarded in v0 through the D_8007359C load, then copies
   to guarded s0 in that load-delay slot; this fixes both equal-length register substitutions. */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct Entity Entity;

struct Entity {
    s8 pad00[0x13];
    u8 kind;
    u32 flags;
    u32 pad18;
    u32 status;
    u8 pad20[0x3C];
    Entity *next;
    u8 pad60[0xD];
    s8 field6D;
    s16 field6E;
    u8 pad70[0x34];
    void *owner;
    u8 padA8[2];
    s16 fieldAA;
};

extern u16 pending_marked_actor_count[];

/* Mark owned entities of kind 0x1E and increment the dungeon counters. */
void mark_owned_linked_actor_actions(Entity *owner_entity) {
    Entity *node;
    ActorRecord *sentinel;
    u16 marked_count;
    u32 node_status;
    u32 incremented_count;

    if (owner_entity->kind == 0x1E) {
        if (owner_entity->flags & 0x4000) {
            if (owner_entity->fieldAA != 0) {
                sentinel = dungeon_actor_ring_anchor;
                node = (Entity *)((u8 *)((Entity *)sentinel->next_actor_header) + 0x20);
                if (node != sentinel) {
                    do {
                        if ((node->kind == 0x1E) &&
                            (node->owner == (void *)((u8 *)owner_entity - 0x20))) {
                            incremented_count = (u16)g_dungeon_status.activity_counts.parts.pending_action_count + 1;
                            g_dungeon_status.activity_counts.parts.pending_action_count = incremented_count;
                            marked_count = pending_marked_actor_count[0];
                            node_status = node->status;
                            node->field6E = 0;
                            incremented_count = marked_count + 1;
                            node_status |= 0x400000;
                            pending_marked_actor_count[0] = incremented_count;
                            node->field6D = 0;
                            node->status = node_status;
                        }
                        node = (Entity *)((u8 *)node->next + 0x20);
                    } while (node != ((Entity *)dungeon_actor_ring_anchor));
                }
            }
        }
    }
}
#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"

typedef struct S_800A32A4_1 {
    u8 pad_00[0x14A8];
    s32 unk_14A8;
} S_800A32A4_1;   /* page_base in detach_record_and_update_slot_state */

typedef struct S_800A32A4_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    void * unk_D0;
} S_800A32A4_2;

typedef struct S_800A32A4_3 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800A32A4_3;

   /* computed_dest in detach_record_and_update_slot_state */

typedef struct S_800A32A4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A32A4_5;

struct S_800E3E48 {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0x8C - 0x20];
};
struct S_16 {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
};
typedef struct S_800E3E48 S_800E3E48;
extern S_800E3E48 familiar_record_storage[];
extern s32 familiar_record_slots[];
extern void clear_slots_of_type(void *, s32);
extern void decrement_monster_entry_count();
extern void mark_owned_linked_actor_actions();

/* Detach a record from its slot, preserve its data, and update its count and state. */
s32 detach_record_and_update_slot_state(void *record) {
    s16 update_mode;
    DungeonGlobalStatus *counter_base;
    s32 slot_offset;
    s32 record_index;
    s32 state_flags;
    s32 tail_w0;
    s32 tail_w4;
    s32 tail_w8;
    s32 *tail_src;
    s32 slot_index;
    FamiliarItemSlotView *dest_base;
    S_800A32A4_2 *slot;
    S_800A32A4_3 *entry;
    void *copy_dst;
    void *copy_src;
    u8 *page_base;
    u8 *status_page;
    S_800E3E48 *copy_base;
    s32 *registry;
    void *copy_end;

    update_mode = 0;
    entry = 0;
    clear_slots_of_type(record, 0x1A);
    clear_slots_of_type(record, 0x1C);
    clear_slots_of_type(record, STATUS_DAMAGE_GUARD);
    if (!(((EntityRec *)record)->flags14 & 0x20000000)) {
        mark_owned_linked_actor_actions(record);
        slot_index = 0;
        page_base = (u8 *)0x80080000;
        copy_src = (void *)~0x4000;
        registry = familiar_record_slots;
        copy_base = familiar_record_storage;
        copy_end = record + 0x80;
scan_slots:
        slot_offset = slot_index * 4;
        slot = slot_offset + ((S_800A32A4_1 *)page_base)->unk_14A8;
        slot_index += 1;
        if (slot->unk_AC == record) {
            ((EntityRec *)record)->flags14 = (s32)(((EntityRec *)record)->flags14 & (s32)copy_src);
            slot->unk_AC = 0;
            state_flags = ((EntityRec *)record)->flags1C;
            state_flags |= 0x04000000;
            state_flags |= 0x00020000;
            ((EntityRec *)record)->flags1C = state_flags;
            entry = slot->unk_D0;
            entry->unk_03 = (u8)(entry->unk_03 & 0xDF);
            dest_base = (void *)((u32)slot_offset + ((S_800A32A4_1 *)page_base)->unk_14A8);
            dest_base->item_address = 0;
            update_mode = 3;
            copy_src = record;
            record_index = entry->unk_03 & 0x1F;
            dest_base = (void *)((record_index * sizeof(*copy_base)) + (s32)copy_base);
            registry[record_index] = (s32)dest_base;
            copy_dst = dest_base;
            do {
                *(struct S_16 *)copy_dst = *(struct S_16 *)copy_src;
                copy_src += 0x10;
                copy_dst += 0x10;
            } while (copy_src != copy_end);
            tail_src = (s32 *)copy_src;
            tail_w0 = tail_src[0];
            tail_w4 = tail_src[1];
            tail_w8 = tail_src[2];
            ((S_800A32A4_5 *)copy_dst)->unk_00 = tail_w0;
            ((S_800A32A4_5 *)copy_dst)->unk_04 = tail_w4;
            ((S_800A32A4_5 *)copy_dst)->unk_08 = tail_w8;
        } else if (slot_index < 4) {
            goto scan_slots;
        }
    }
    if (update_mode == 0) {
        state_flags = ((EntityRec *)record)->flags14;
        update_mode = 3;
        if (!(state_flags & 0x4000)) {
            status_page = (u8 *)(state_flags & 0x2000);
            if (status_page) {
                counter_base = &g_dungeon_status;
                if (counter_base->monster_count != 0) {
                    counter_base->monster_count = (s16)(((u16)counter_base->monster_count) - 1);
                }
                update_mode = 2;
            } else {
                DungeonGlobalStatus *counter_base;
                counter_base = &g_dungeon_status;
                if (counter_base->monster_count != 0) {
                    counter_base->monster_count = (s16)(((u16)counter_base->monster_count) - 1);
                }
                update_mode = 1;
            }
        }
    }
    if (!(((EntityRec *)record)->flags14 & 0x20000000)) {
        decrement_monster_entry_count((*(u8 *)((u8 *)&((EntityRec *)record)->unk_10 + 3)), update_mode);
    }
    return (s32)entry;
}
