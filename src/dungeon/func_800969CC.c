#include "modules/dungeon_engine_transition_effects_abi_views.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
extern u8 D_800E0000[];

#define M2C_BREAK() 0

s32 func_8003AD08();
void func_800419EC();
s32 func_80042900();
void clear_player_linked_action_flags();
s32 clamp_adjusted_value_0_to_99();
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
extern void * func_80099290(s8 *byte_ptr);
s32 write_text_byte_and_advance();
s32 apply_type_based_entry_adjustments();
s32 append_entity_display_text();
extern void create_type_212_object(s32 flag, s8 value);
void add_random_quarter_value();
s32 get_masked_record_flags();
void accumulate_experience_award();
s32 play_sound_if_enabled();
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
s16 find_directional_entry_and_clear_flag();
s32 prepare_quarter_damage_return();
s32 count_occupied_entity_slots();
extern M2C_UNK D_800E0D7B;
extern M2C_UNK D_800E0D92;
extern M2C_UNK D_800E0D9E;
extern M2C_UNK D_800E0DB8;
extern M2C_UNK D_800E0DDD;
extern M2C_UNK D_800E0DEA;
extern M2C_UNK D_800E3648;


typedef struct S_8009C12C_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s32 unk_1C;
    union { u16 n; u16 v; } unk_20;   /* accessed as both */
    u8 pad_22[0x8];
    s16 unk_2A;
    u8 pad_2C[0x20];
    u16 * unk_4C;
    u8 pad_50[0x10];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    s16 unk_88;
    u8 pad_8A[0x1C];
    s16 unk_A6;
    u8 unk_A8;
} S_8009C12C_0;   /* arg0 in resolve_attack_damage_and_effects */

typedef struct S_8009C12C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8009C12C_2;   /* arg1 in resolve_attack_damage_and_effects */

typedef struct S_8009C12C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009C12C_3_pre;   /* 0x14-byte header immediately before the payload. */

typedef struct S_8009C12C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x2];
    union { u16 n; u16 v; s16 n2; } unk_22;   /* accessed as both */
    u8 pad_24[0x3];
    u8 unk_27;
    u8 pad_28[0x38];
    void * unk_60;
    union { s16 n; s16 v; } unk_64;   /* accessed as both */
    u8 pad_66[0x22];
    u16 unk_88;
} S_8009C12C_3;

typedef struct S_8009C12C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x3D66];
    void * unk_3D7C;
} S_8009C12C_4;

typedef struct S_8009C12C_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_8009C12C_7;   /* table_v0 in resolve_attack_damage_and_effects */

/* Resolve an attack against the linked target and display its damage and effects. */
void *resolve_attack_damage_and_effects(void *attacker_in, void *tile_in, s16 direction, s16 distance) {
    s16 tile_result;
    s16 height_diff;
    s32 damage;
    s16 message_state;
    s16 *opposite_x_ptr;
    s32 d;
    s32 opp;
    s32 x;
    s32 y;
    s32 ox;
    s32 oy;
    s32 target_flags;
    s32 target_elements;
    u32 attack_elements;
    s32 message_start;
    s32 attack_bonus;
    s8 attacker_kind;
    s32 half_delta;
    s32 attacker_blocked;
    s32 quarter_delta;
    s32 effect_elements;
    u32 effect_flags;
    u32 message_cursor;
    s32 modifier;
    s32 element_match;
    s32 element_check;
    s32 scaled_modifier;
    s32 signed_value;
    u16 *attack_script;
    u16 target_traits;
    u8 kind_check;
    S_8009C12C_4 *target_data;
    s32 element_product;
    void *target;
    void *blocked_actor;
    void *null_result;

    modifier = 0;
    ((S_8009C12C_0 *)attacker_in)->unk_73 = 0;
    ((S_8009C12C_0 *)attacker_in)->unk_72 = 0;
    target = ((S_8009C12C_0 *)attacker_in)->unk_60;
    message_state = modifier;
    if (target == NULL) {
        null_result = NULL;
        if (attacker_in == (void *)D_800E3D7C) {
            tile_result = find_directional_entry_and_clear_flag(((S_8009C12C_2 *)(tile_in))->unk_24, ((S_8009C12C_2 *)(tile_in))->unk_25,
                direction, ((S_8009C12C_0 *)attacker_in)->unk_88);
            null_result = NULL;
            if (tile_result >= 0) {
                s32 tile_text;
                s32 tile_text_base;
                message_start = get_unused_text_buffer();
                message_cursor = write_text_byte_and_advance(8, message_start);
                tile_text = tile_result << 2;
                tile_text_base = (s32)&D_800E3648;
                tile_text += tile_text_base;
                message_cursor = apply_type_based_entry_adjustments(tile_text, message_cursor);
                message_cursor = expand_text_control_codes(&D_800E0D7B, message_cursor);
                func_80099290(message_cursor);
                display_text_with_fullwidth_adjustment(message_start);
                play_sound_if_enabled(0x700);
                accumulate_experience_award(attacker_in, 8);
                create_actor_value_popup(0x82, attacker_in, 8, 1);
            }
        }
        return NULL;
    }
    message_start = get_unused_text_buffer();
    message_cursor = message_start;
    attacker_kind = ((S_8009C12C_0 *)attacker_in)->unk_13;
    kind_check = *(u8 *)((s8 *)attacker_in + 0x13);
    if (attacker_kind >= 0) {
        target_data = ((S_8009C12C_3_pre *)target)[-1].unk_00;
        target_traits = target_data->unk_14;
        if (!(((S_8009C12C_2 *)(tile_in))->unk_14 & target_traits & 0x8000)
            || ((kind_check == 0x23) && (((S_8009C12C_0 *)attacker_in)->unk_A6 != 0) && !(target_traits & 0x8000))) {
            message_cursor = append_entity_display_text(attacker_in, message_start);
            message_cursor = expand_text_control_codes(&D_800E0D92, message_cursor);
            message_cursor = write_text_byte_and_advance(0xA, message_cursor);
        } else {
            attacker_blocked = ((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x4000;
            if ((attacker_blocked != 0) || (message_state = -1, ((((S_8009C12C_3 *)target)->unk_14 & 0x4000) != 0))) {
                blocked_actor = target;
                if (attacker_blocked != 0) {
                    blocked_actor = attacker_in;
                }
                message_cursor = append_entity_display_text(blocked_actor, message_cursor);
                message_cursor = expand_text_control_codes(&D_800E0D9E, message_cursor);
                message_state = 1;
            }
        }
        ((S_8009C12C_3 *)target)->unk_14 = (s32) (((S_8009C12C_3 *)target)->unk_14 | 0x01000000);
    } else {
        ((S_8009C12C_3 *)target)->unk_14 = (s32) (((S_8009C12C_3 *)target)->unk_14 | 0x01000000);
    }
    if (((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x04000000) {
        create_actor_value_popup(3, target, -1, 0);
        if (((S_8009C12C_0 *)attacker_in)->unk_13 >= 0) {
            signed_value = message_state << 16;
            modifier = signed_value >> 16;
            if (modifier == 0) {
                message_cursor = append_entity_display_text(target, message_cursor);
                message_cursor = expand_text_control_codes(&D_800E0DB8, message_cursor);
            }
            null_result = NULL;
            if (modifier >= 0) {
                func_80099290(message_cursor);
                display_text_with_fullwidth_adjustment(message_start);
                return (void *)0;
            }
            return null_result;
        }
        return (void *)0;
    }
    attack_script = ((S_8009C12C_0 *)attacker_in)->unk_4C;
    if ((attack_script != NULL) && (*attack_script == 0xF0D)) {
        ((S_8009C12C_3 *)target)->unk_22.n = ((S_8009C12C_3 *)target)->unk_27;
    } else {
        ((S_8009C12C_3 *)target)->unk_22.v = (u16) (((S_8009C12C_3 *)target)->unk_27 + clamp_adjusted_value_0_to_99(target));
    }
    if ((func_80042900(target, 0xA) << 0x10) != 0) {
        ((S_8009C12C_3 *)target)->unk_22.n = (u16) ((s32) (((S_8009C12C_3 *)target)->unk_22.n << 0x10) >> 0x11);
    }
    {
        s16 defense = ((S_8009C12C_3 *)target)->unk_22.n2;
        u16 defense_raw = ((S_8009C12C_3 *)target)->unk_22.v;
        if (defense == 0) {
            ((S_8009C12C_3 *)target)->unk_22.n = (u16) (defense_raw + 1);
        }
    }
    attack_elements = get_masked_record_flags(attacker_in, 7, 1);
    target_elements = get_masked_record_flags(target, 7, 0);
    if (attack_elements & 1) {
        if ((func_80042900(target, 0x13) << 0x10) != 0) {
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10)
                >> 0x12);
        } else {
            if (target_elements & 4) {
                modifier += 1;
            }
            element_match = target_elements & 2;
            if (element_match) {
                modifier -= 2;
            }
        }
    }
    element_match = attack_elements & 2;
    if (element_match != 0) {
        if ((func_80042900(target, 0x14) << 0x10) != 0) {
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10)
                >> 0x12);
        } else {
            if (target_elements & 1) {
                modifier += 1;
            }
            element_check = target_elements & 4;
            if (element_check) {
                modifier -= 2;
            }
        }
    }
    element_check = attack_elements & 4;
    if (element_check != 0) {
        if ((func_80042900(target, 0x12) << 0x10) != 0) {
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10)
                >> 0x12);
        } else {
            element_check = target_elements & 2;
            if (element_check) {
                modifier += 1;
            }
            element_check = target_elements & 1;
            if (element_check) {
                modifier -= 2;
            }
        }
    }
    height_diff = (u16) ((S_8009C12C_0 *)attacker_in)->unk_88 - ((S_8009C12C_3 *)target)->unk_88;
    if (height_diff >= 0x20) {
        modifier -= 1;
    } else {
        scaled_modifier = height_diff < -0x1F;
        if (scaled_modifier == 0) {
            scaled_modifier = modifier << 0x10;
        } else {
            modifier += 1;
            scaled_modifier = modifier << 0x10;
        }
    }
    scaled_modifier = modifier << 0x10;
    {
        s32 attack_value;
        u16 attack_raw;
        void *bonus_actor;
        attack_value = (s16)((S_8009C12C_0 *)attacker_in)->unk_20.n;
        element_product = attack_value * (scaled_modifier >> 0x10);
        bonus_actor = attacker_in;
        attack_raw = ((S_8009C12C_0 *)attacker_in)->unk_20.v;
        attack_value = element_product >> 3;
        ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16)(attack_raw + attack_value);
        attack_bonus = count_occupied_entity_slots(bonus_actor);
    }
    if (attack_bonus != 0) {
        u16 bonus_base;
        bonus_base = ((S_8009C12C_0 *)attacker_in)->unk_20.n;
        ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16)(bonus_base + ((s16)bonus_base >> 3) * attack_bonus);
    }
    if (((S_8009C12C_0 *)attacker_in)->unk_1C & 0x01000000) {
        half_delta = (s32) ((s16) ((S_8009C12C_3 *)target)->unk_22.n
            - (s16) ((S_8009C12C_0 *)attacker_in)->unk_20.n) / 2;
        quarter_delta = (s32) ((s16) half_delta + ((u32) (half_delta << 0x10) >> 0x1F)) >> 1;
        ((S_8009C12C_3 *)target)->unk_64.n = (s16) (half_delta + quarter_delta);
    } else {
        ((S_8009C12C_3 *)target)->unk_64.v = (s16) ((s32) ((s16) ((S_8009C12C_3 *)target)->unk_22.n
            - (s16) ((S_8009C12C_0 *)attacker_in)->unk_20.n) / 2);
    }
    if (((S_8009C12C_3 *)target)->unk_64.n >= 0) {
        ((S_8009C12C_3 *)target)->unk_64.n = -1;
    }
    modifier = func_80042900(target, 0x1D);
    signed_value = message_state;
    signed_value <<= 0x10;
    if (signed_value == 0) {
        message_cursor = append_entity_display_text(target, message_cursor);
        {
            if (((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x2000) {
                message_cursor = expand_text_control_codes(D_800E0000 + 0xDD0, message_cursor);
            } else {
                message_cursor = expand_text_control_codes(&D_800E0DDD, message_cursor);
            }
        }
        {
            s32 display_damage;
            if ((modifier << 0x10) != 0) {
                display_damage = 0;
                message_cursor = func_8003AD08(display_damage, message_cursor);
            } else {
                display_damage = ((S_8009C12C_3 *)target)->unk_64.n;
                display_damage = 0 - display_damage;
                message_cursor = func_8003AD08(display_damage, message_cursor);
            }
        }
        message_cursor = expand_text_control_codes(&D_800E0DEA, message_cursor);
        signed_value = message_state << 0x10;
    }
    if (signed_value >= 0) {
        func_80099290(message_cursor);
        display_text_with_fullwidth_adjustment(message_start);
    }
    if (distance == 1) {
        prepare_quarter_damage_return(attacker_in, target);
    }
    effect_flags = 0xDFFFFFFF;
    target_data = (S_8009C12C_4 *)D_800E0000;
    target_flags = ((S_8009C12C_3 *)target)->unk_1C & effect_flags;
    target_data = target_data->unk_3D7C;
    ((S_8009C12C_3 *)target)->unk_1C = target_flags;
    if (target == target_data) {
        add_random_quarter_value(target, attacker_in);
    }
    signed_value = modifier << 0x10;
    damage = 0;
    if (signed_value == 0) {
        signed_value = 0 - (u16) ((S_8009C12C_3 *)target)->unk_64.n;
        signed_value <<= 0x10;
        damage = signed_value >> 0x10;
    }
    create_actor_value_popup(3, target, damage, 0);
    if (target == (void *)D_800E3D7C) {
        clear_player_linked_action_flags();
    }
    ((S_8009C12C_3 *)target)->unk_60 = attacker_in;
    ((S_8009C12C_0 *)attacker_in)->unk_60 = target;
    g_dungeon_status.unk_10 = target - 0x20;
    if (((S_8009C12C_0 *)attacker_in)->unk_1C & 0x01000000) {
        opposite_x_ptr = (s16 *)(4);
        play_sound_if_enabled(0x700);
        effect_flags = ((S_8009C12C_0 *)attacker_in)->unk_14.u16;
        effect_flags &= 0x2000;
        effect_flags <<= 0x10;
        effect_flags >>= 0x10;
        create_type_212_object(effect_flags, (s32)opposite_x_ptr);
    }
    play_sound_if_enabled(0x601);
    if (!(((S_8009C12C_2 *)(tile_in))->unk_14 & 0x8000)) {
        func_800419EC(8, 0x10);
    }
    effect_elements = attack_elements << 0x10;
    if (attacker_in == (void *)D_800E3D7C) {
        if (((S_8009C12C_0 *)attacker_in)->unk_A8 != 0) {
            return target;
        }
    }
    effect_elements = attack_elements << 0x10;
    effect_elements >>= 0x10;
    d = (u16)direction >> 9 & 7;
    x = ((S_8009C12C_2 *)tile_in)->unk_24 + dir_step_x[d] * distance;
    opp = (d + 4) & 7;
    ox = (dir_step_x[opp] << 5) + 0x20;
    y = ((S_8009C12C_2 *)tile_in)->unk_25 + dir_step_y[d] * distance;
    oy = (dir_step_y[opp] << 5) + 0x20;
    transition_effect_legacy((s16)((x << 6) + ox), (s16)((y << 6) + oy),
        (s16)(((S_8009C12C_7 *)((S_8009C12C_0 *)attacker_in)->unk_60)->unk_88 - 0x30), effect_elements,
        ((S_8009C12C_0 *)attacker_in)->unk_2A);
    return target;
}
