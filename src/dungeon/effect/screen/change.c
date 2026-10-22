/* Complete native TU in retail file order. Review pending. */
#include "dungeon/effect/screen/change.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80083160.h"

typedef struct S_8009BE2C_1 {
    u8 pad_00[0x3];
    s8 unk_03;
    union {
        struct { s8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; s8 v; } at01;
        struct { u8 pad[0x2]; s8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_04;   /* overlapping accesses */
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} S_8009BE2C_1;

typedef struct S_8009BE2C_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    s16 unk_06;
} S_8009BE2C_2;   /* arg2 in draw_fullscreen_fade */

typedef struct S_8009BE2C_3 {
    void * unk_00;
} S_8009BE2C_3;

typedef struct S_8009BE2C_4_pre {
    u16 unk_00;
} S_8009BE2C_4_pre;   /* the 0x2 bytes before arg0 in draw_fullscreen_fade, addressed as arg0[-1] */

typedef struct S_8009BE2C_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_8009BE2C_5;   /* ((Rec_D_80083160 *)(&D_80083160))->unk_00.as_pv in draw_fullscreen_fade */

typedef struct S_8009BE2C_6 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_8009BE2C_6;

/* cfail-repair: tf7-phase1-cache-v3 */
struct S_8003E2D8;
typedef struct S_8003E2D8 S_8003E2D8;
extern s32 func_8006658C(void *, void *);              /* extern */
extern s32 func_800667A8(void *, s32);                  /* extern */

/* Draw a full-screen fade and mark the effect complete when its countdown ends. */
void draw_fullscreen_fade(void *effect, s32 unused, S_8009BE2C_2 *fade) {
    s32 intensity;
    s16 color_value;
    s8 frames_left;
    void *packet;
    void **render_context;

    packet = ((S_8009BE2C_5 *)(((Rec_D_80083160 *)(((struct S_8003E2D8 *)&g_game_work)))->unk_00.as_pv))->unk_8D0;
    ((S_8009BE2C_5 *)(((Rec_D_80083160 *)(((struct S_8003E2D8 *)&g_game_work)))->unk_00.as_pv))->unk_8D0 =
        (void *) (packet + 0x10);
    ((S_8009BE2C_1 *)packet)->unk_0C = 0x140;
    ((S_8009BE2C_1 *)packet)->unk_08 = 0;
    ((S_8009BE2C_1 *)packet)->unk_0A = 0;
    ((S_8009BE2C_1 *)packet)->unk_0E = 0xE0;
    intensity = (0xC0 / (s16) fade->unk_06) * fade->unk_05;
    color_value = intensity;
    render_context = (void **)((struct S_8003E2D8 *)&g_game_work);
    if (fade->unk_04 != 0) {
        ((S_8009BE2C_1 *)packet)->unk_04.at02.v = color_value;
        ((S_8009BE2C_1 *)packet)->unk_04.at01.v = color_value;
        ((S_8009BE2C_1 *)packet)->unk_04.at00.v = color_value;
    } else {
        ((S_8009BE2C_1 *)packet)->unk_04.at00u.v = (s32) (s16) color_value;
    }
    func_800667A8(packet, intensity);
    ((S_8009BE2C_1 *)packet)->unk_04.at03.v = (u8) (((S_8009BE2C_1 *)packet)->unk_04.at03.v | 2);
    func_8006658C(((S_8009BE2C_3 *)render_context)->unk_00 + 0xB0, packet);
    packet = ((S_8009BE2C_6 *)(((S_8009BE2C_3 *)render_context)->unk_00))->unk_8D0;
    ((S_8009BE2C_6 *)(((S_8009BE2C_3 *)render_context)->unk_00))->unk_8D0 = (void *) (packet + 0xC);
    ((S_8009BE2C_1 *)packet)->unk_03 = 1;
    ((S_8009BE2C_1 *)packet)->unk_04.at00u.v = 0xE1000020;
    func_8006658C(((S_8009BE2C_3 *)render_context)->unk_00 + 0xB0, packet);
    frames_left = (u8) fade->unk_05 - 1;
    fade->unk_05 = frames_left;
    if ((frames_left << 0x18) == 0) {
        ((S_8009BE2C_4_pre *)effect)[-1].unk_00 = (u16) (((S_8009BE2C_4_pre *)effect)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | 0x8000;
    }
}
#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef struct S_8009BF7C_2 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_8009BF7C_2;

void *allocate_list_node();                  /* extern */
extern M2C_UNK D_8009BE2C;

typedef struct S_8009BF7C_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s32 * unk_10;
} S_8009BF7C_0;

/* Creates a type 0x212 object and initializes its flag and value. */
void create_type_212_object(s32 flag, s8 value) {
    SpriteFrameState *state;
    S_8009BF7C_0 *object;

    object = allocate_list_node(0x212, ((s32)dungeon_actor_ring_anchor) - 0x20);
    if (object != NULL) {
        state = object->unk_0C;
        object->unk_10 = &D_8009BE2C;
        state->unk_05 = value;
        state->unk_06 = (s16) value;
        ((SpriteFrameState *)((S_8009BF7C_2 *)object)->unk_0C)->unk_04 = (s8) ((flag << 0x10) != 0);
    }
}
#include "common.h"

#define NULL ((void *)0)

s32 generate_random_value(void);
s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(u8 *src, u8 *dst);
s32 format_unsigned_double_byte_decimal(s32, s32);
s32 append_entity_display_text(void *record, u8 *out);
extern void * clear_byte_and_advance(s8 *byte_ptr);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_80088CAC[];
extern u8 D_800E0D51[];
extern u8 D_800E0D6D[];

/* Randomly adds a quarter of the source value to the target and reports the change. */
void add_random_quarter_value(void *source, void *target) {
    int direction_aux;
    s32 amount;
    s16 signed_amount;
    s32 message_start;
    s32 message_end;
    u8 *type_data;
    void *source_entity;
    void *target_entity;

    type_data = *(u8 **)((s8 *)source + 0x50);
    if (type_data != NULL && *type_data == 0xB && !(generate_random_value() & 3)) {
        amount = ((s32)(*(u16 *)((s8 *)source + 0x64) << 0x10)) >> 0x12;
        signed_amount = amount;
        *(u16 *)((s8 *)target + 0x64) += amount;
        if (signed_amount != 0) {
            source_entity = *(void **)((s8 *)source - 0x14);
            target_entity = *(void **)((s8 *)target - 0x14);
            *(void **)((s8 *)target + 0x60) = source;
            *(s16 *)((s8 *)target + 0x6A) = get_rounded_facing_and_rounding_flag(
                *(u8 *)((s8 *)source_entity + 0x24),
                *(u8 *)((s8 *)source_entity + 0x25),
                *(u8 *)((s8 *)target_entity + 0x24),
                *(u8 *)((s8 *)target_entity + 0x25),
                &direction_aux
                );
            create_actor_value_popup(3, target, -amount, 0);
            message_end = get_unused_text_buffer();
            message_start = message_end;
            message_end = expand_text_control_codes(D_800E0D51, message_start);
            message_end = format_unsigned_double_byte_decimal(-signed_amount, message_end);
            message_end = expand_text_control_codes(D_800E0D6D, message_end);
            message_end = append_entity_display_text(target, message_end);
            message_end = expand_text_control_codes(D_80088CAC, message_end);
            clear_byte_and_advance(message_end);
            display_text_with_fullwidth_adjustment(message_start);
        }
    }
}
#include "modules/dungeon_engine_transition_effects_abi_views.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

typedef struct ActiveEntry { u8 pad0; u8 active; u8 pad2[2]; } ActiveEntry;
extern u8 D_800E0000[];

s32 format_unsigned_double_byte_decimal();
void initialize_timed_motion_step();
s32 get_entity_effect_value();
void clear_player_linked_action_flags();
s32 clamp_adjusted_value_0_to_99();
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
extern void * clear_byte_and_advance(s8 *byte_ptr);
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
extern u8 D_800E0D7B[23];
extern u8 D_800E0D92[12];
extern u8 D_800E0D9E[26];
extern u8 D_800E0DB8[24];
extern u8 D_800E0DDD[13];
extern u8 D_800E0DEA[11];
extern ActiveEntry floor_objects[32];

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
        if (attacker_in == (void *)dungeon_actor_ring_anchor) {
            tile_result = find_directional_entry_and_clear_flag(((S_8009C12C_2 *)(tile_in))->unk_24, ((S_8009C12C_2 *)(tile_in))->unk_25,
                direction, ((S_8009C12C_0 *)attacker_in)->unk_88);
            null_result = NULL;
            if (tile_result >= 0) {
                s32 tile_text;
                s32 tile_text_base;
                message_start = get_unused_text_buffer();
                message_cursor = write_text_byte_and_advance(8, message_start);
                tile_text = tile_result << 2;
                tile_text_base = (s32)&floor_objects;
                tile_text += tile_text_base;
                message_cursor = apply_type_based_entry_adjustments(tile_text, message_cursor);
                message_cursor = expand_text_control_codes(D_800E0D7B, message_cursor);
                clear_byte_and_advance(message_cursor);
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
            message_cursor = expand_text_control_codes(D_800E0D92, message_cursor);
            message_cursor = write_text_byte_and_advance(0xA, message_cursor);
        } else {
            attacker_blocked = ((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x4000;
            if ((attacker_blocked != 0) || (message_state = -1, ((((S_8009C12C_3 *)target)->unk_14 & 0x4000) != 0))) {
                blocked_actor = target;
                if (attacker_blocked != 0) {
                    blocked_actor = attacker_in;
                }
                message_cursor = append_entity_display_text(blocked_actor, message_cursor);
                message_cursor = expand_text_control_codes(D_800E0D9E, message_cursor);
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
                message_cursor = expand_text_control_codes(D_800E0DB8, message_cursor);
            }
            null_result = NULL;
            if (modifier >= 0) {
                clear_byte_and_advance(message_cursor);
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
    if ((get_entity_effect_value(target, 0xA) << 0x10) != 0) {
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
        if ((get_entity_effect_value(target, 0x13) << 0x10) != 0) {
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
        if ((get_entity_effect_value(target, 0x14) << 0x10) != 0) {
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
        if ((get_entity_effect_value(target, 0x12) << 0x10) != 0) {
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
    modifier = get_entity_effect_value(target, 0x1D);
    signed_value = message_state;
    signed_value <<= 0x10;
    if (signed_value == 0) {
        message_cursor = append_entity_display_text(target, message_cursor);
        {
            if (((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x2000) {
                message_cursor = expand_text_control_codes(D_800E0000 + 0xDD0, message_cursor);
            } else {
                message_cursor = expand_text_control_codes(D_800E0DDD, message_cursor);
            }
        }
        {
            s32 display_damage;
            if ((modifier << 0x10) != 0) {
                display_damage = 0;
                message_cursor = format_unsigned_double_byte_decimal(display_damage, message_cursor);
            } else {
                display_damage = ((S_8009C12C_3 *)target)->unk_64.n;
                display_damage = 0 - display_damage;
                message_cursor = format_unsigned_double_byte_decimal(display_damage, message_cursor);
            }
        }
        message_cursor = expand_text_control_codes(D_800E0DEA, message_cursor);
        signed_value = message_state << 0x10;
    }
    if (signed_value >= 0) {
        clear_byte_and_advance(message_cursor);
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
    if (target == (void *)dungeon_actor_ring_anchor) {
        clear_player_linked_action_flags();
    }
    ((S_8009C12C_3 *)target)->unk_60 = attacker_in;
    ((S_8009C12C_0 *)attacker_in)->unk_60 = target;
    g_dungeon_status.pending_display_owner = target - 0x20;
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
        initialize_timed_motion_step(8, 0x10);
    }
    effect_elements = attack_elements << 0x10;
    if (attacker_in == (void *)dungeon_actor_ring_anchor) {
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
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"

typedef struct Ent {
    u8 pad0[3];        /* 0x00 */
    u8 unk3;           /* 0x03 */
    u8 pad4[0xF];      /* 0x04 */
    u8 unk13;          /* 0x13 */
    s32 flags14;       /* 0x14 */
    u8 pad18[4];       /* 0x18 */
    u32 flags1c;       /* 0x1C */
    u16 unk20;         /* 0x20 */
    u8 pad22[4];       /* 0x22 */
    u8 unk26;          /* 0x26 */
    u8 pad27[3];       /* 0x27 */
    u16 unk2a;         /* 0x2A */
    u8 pad2c[0x1A];    /* 0x2C */
    u16 unk46;         /* 0x46 */
    u8 pad48[8];       /* 0x48 */
    u8 *unk50;         /* 0x50 */
    u8 pad54[0xC];     /* 0x54 */
    struct Ent *unk60; /* 0x60 */
    u8 pad64[6];       /* 0x64 */
    u16 unk6a;         /* 0x6A */
    u8 pad6c[4];       /* 0x6C */
    u8 unk70;          /* 0x70 */
    u8 pad71[0x13];    /* 0x71 */
    u8 unk84;          /* 0x84 */
    u8 pad85[3];       /* 0x85 */
    s16 unk88;         /* 0x88 */
} Ent;

typedef struct {
    u8 pad0[0x24];
    u8 unk24;          /* 0x24 */
    u8 unk25;          /* 0x25 */
} Pos;

extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];

extern s32 generate_random_value();
extern void setup_object_within_planar_range(void *, s32, s32, s32, s32, s32);
extern s32 check_diagonal_side_height(s32, s32, s32, s32);
extern Ent *find_eligible_actor_at_tile_and_height(Ent *, s32, s32, s32);
extern s32 get_clamped_adjusted_value(Ent *);
extern void func_8003E188(s32, s32);

/* Finds a directional attack target, updates facing and hit flags, and rolls attack and evasion values. */
Ent *prepare_directional_attack(Ent *a, Pos *b, u32 coordArg, s32 mult, Ent *ent2) {
    s32 zero = 0;
    u16 coord;
    s32 savedMult;
    s32 off;
    s32 shifted;
    s32 value;
    s32 step;
    u8 *base;
    u16 *tableA;

    coord = coordArg;
    savedMult = mult;
    if (ent2 == 0) {
        s32 f;
        u32 nc;

        base = (u8 *)a - 0x20;
        if ((a->flags1c & 0x400) != 0 && ((f = a->flags14) & 0x80000000) == 0) {
            f |= 0x80000000;
            a->flags14 = f;
            nc = coordArg + ((generate_random_value() & 7) << 9);
            coord = nc;
            a->unk2a = nc;
        }
    }
    base = (u8 *)a - 0x20;
    shifted = coord >> 8;
    tableA = direction_x_offsets;
    off = shifted & 0xE;

    setup_object_within_planar_range(base,
                  (b->unk24 << 6) + ((s16)*(u16 *)((u8 *)tableA + off) >> 1) + 0x20,
                  (b->unk25 << 6) + ((s16)*(u16 *)((u8 *)direction_y_offsets + off) >> 1) + 0x20,
                  a->unk88, 8, 0x300);
    a->unk60 = ent2;
    a->flags14 &= ~0x4000000;
    if (ent2 == 0) {
        /*
         * Original bug: The Salamander passes distance zero and no explicit target. The diagonal corner check can still
         * reject a wall beside this same-tile attack, leaving unk60 null and dealing no damage.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        if ((check_diagonal_side_height((a->unk2a >> 9) & 7, b->unk24, b->unk25,
                           (s16)(*(u16 *)&a->unk88 - 0x20)) << 16) != 0) {
            ent2 = find_eligible_actor_at_tile_and_height(a,
                                 (u16)(b->unk24 + *(u16 *)((u8 *)dir_step_x + off) * savedMult),
                                 (u16)(b->unk25 + *(u16 *)((u8 *)dir_step_y + off) * savedMult),
                                 a->unk88);
            a->unk60 = ent2;
            if (ent2 == 0) {
                return 0;
            }
        } else {
            return 0;
        }
    }
    ent2->unk6a = a->unk2a;
    if (ent2->unk13 != 0 && (ent2->flags1c & 0x238) == 0 && (ent2->unk46 & 0x8000) == 0) {
        ent2->unk2a = a->unk2a + 0x800;
    }
    a->flags14 |= 0x4000000;
    ent2->flags14 = (ent2->flags14 | 0x20000) & ~0x1000000;

    {
        u8 dance;

        dance = a->unk84;
        value = dance;
        {
            s32 r = generate_random_value() & 0xFFFF;

            step = (s16)value;
            if (a->unk3 != 0) {
                r %= a->unk3;
                r <<= 2;
                value = step + r;
            } else {
                value = step;
            }
        }

    }
    if (ent2->unk13 == 0) {
        u8 *p = ent2->unk50;

        if (p != 0 && *p == 2) {
            value -= (s16)value >> 2;
        }
    }
    if ((ent2->flags1c & 0x238) == 0 && (s16)value < 0x80) {
        return ent2;
    }
    value = generate_random_value();
    {

        s32 low_bit = value & 1;
        s32 masked = value & 2;
        s32 flag = masked != 0;
        s32 sum = low_bit + flag;
        
        step = sum + (a->unk26 + (s16)get_clamped_adjusted_value(a)) * 2;
    }
    a->unk20 = step;
    if (a->flags1c & 0x1000) {
        value = a->unk3 >> 1;
    } else {
        value = a->unk3 >> 6;
    }
    if ((s16)value >= (s32)(generate_random_value() & 0x7F)) {
        a->flags1c |= 0x1000000;
    } else {
        a->flags1c &= ~0x1000000;
    }
    /*
     * Original bug: the luck dodge roll is limited to incapacitated targets and adds an evasion byte left at zero.
     * Capable targets skip the roll entirely.
     * Found and documented by the Azure Dreams community
     * (adrando.com/guide/bugs.html).
     */
    if ((ent2->flags1c & 0x238) != 0) {
        u8 d;
        s32 rnd;

        rnd = generate_random_value() & 0xFFFF;
        d = ent2->unk3;

        if (d != 0) {
            value = (rnd % ent2->unk3) + zero;
        } else {
            value = 0;
        }
        if (((s16)(s32)((u8 *)value + ent2->unk70) >> 7) > 0) {
            return ent2;
        }
    }
    a->flags14 &= ~0x4000000;
    ent2->flags14 &= ~0x20000;
    if ((u8 *)a == ((u8 *)dungeon_actor_ring_anchor)) {
        func_8003E188(ent2->unk13, 0);
    }
    return ent2;
}
#include "common.h"
#include "shared/entity.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8009CD58_1 {
    u8 unk_00;
    u8 unk_01;
} S_8009CD58_1;   /* temp_a0_3 in get_masked_record_flags */

/* Returns masked record flags augmented by the selected kind. */
s32 get_masked_record_flags(EntityRec *record, s32 mask, s32 mode) {
    s32 shifted_mode;
    s32 base_flags;
    s32 flags;
    s32 third_kind;
    u8 *kind_ptr;
    s32 kind;
    S_8009CD58_1 *detail;

    base_flags = (*(u16 *)&record->flags14) & mask;
    shifted_mode = mode << 16;
    flags = base_flags;
    if (shifted_mode != 0) {
        detail = record->unk_4C;
        if (detail != NULL) {
            if (detail->unk_01 == 15) {
                kind = detail->unk_00;
                if (kind == 5) {
                    third_kind = mask & 1;
                } else if (kind == 6) {
                    third_kind = mask & 2;
                } else {
                    third_kind = 7;
                    if (kind != third_kind) {
                        return flags;
                    }
                    third_kind = mask & 4;
                }
            } else {
                kind = detail->unk_00;
                if (kind == 6) {
                    third_kind = mask & 1;
                } else if (kind == 7) {
                    third_kind = mask & 2;
                } else {
                    third_kind = 8;
                    if (kind != third_kind) {
                        return flags;
                    }
                    third_kind = mask & 4;
                }
            }
            flags = base_flags | third_kind;
        }
        return flags;
    }
    kind_ptr = (*(u8 * *)&record->unk_50);
    if (kind_ptr != NULL) {
        kind = *kind_ptr;
        if (kind == 8) {
            third_kind = mask & 1;
        } else if (kind == 9) {
            third_kind = mask & 2;
        } else {
            third_kind = 10;
            if (kind != third_kind) {
                return flags;
            }
            third_kind = mask & 4;
        }
        flags = base_flags | third_kind;
    }
    return flags;
}
#include "modules/dungeon_engine_transition_effects_abi_views.h"
#include "shared/entity.h"
#include "records/Rec_D_800287A4.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
typedef struct S_8009CE1C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009CE1C_3_pre;   /* the 0x14 bytes before arg0 in apply_attack_power_and_element_effects, addressed as arg0[-1] */

typedef struct S_8009CE1C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_8009CE1C_0;   /* *D_800E3D7C in apply_attack_power_and_element_effects */

typedef struct S_8009CE1C_1 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    u8 pad_28[0x8];
    s32 unk_30;
    u8 pad_34[0x2];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    u8 pad_38[0x3];
    u8 unk_3B;
    u8 pad_3C[0x2];
    u16 unk_3E;
    u8 pad_40[0x1A];
    u16 unk_5A;
    u8 pad_5C[0x18];
    s32 unk_74;
    union { u16 s; s16 u; } unk_78;   /* accessed as both */
    u8 pad_7A[0x4];
    u16 unk_7E;
    u8 pad_80[0x1C];
    u16 unk_9C;
} S_8009CE1C_1;   /* arg0 in apply_attack_power_and_element_effects; pointer addresses record offset 0x14 */

extern u8 pending_player_damage_kind;
void clear_player_linked_action_flags(void);
s32 clamp_adjusted_value_0_to_99();
s32 func_8009CFB4();
s32 func_8009CFF4();
s32 func_8009D034();
extern s32 try_trigger_target_record_effect(ActorRecord *entity, s32 flags, Rec_D_800287A4 *record);
s32 play_sound_if_enabled(s32);
extern void * create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);

/* Compute elemental damage for a target and trigger its hit response. */
void apply_attack_power_and_element_effects(void *target, s16 base_power, s16 power_bonus, s16 elements,
                   u16 hit_angle, s32 source_flags, u16 hit_kind) {
    s32 event_id;
    s16 affinity_product;
    s32 shown_damage;
    s16 bonus;
    s16 affinity_adjust;
    s32 power;
    s32 target_elements;
    s32 damage_delta;
    s32 direction_offset;
    s32 affinity;
    s16 requested_bonus;
    s32 affinity_shift;
    SpriteFrameState *position;
    register u16 base = base_power;
    s16 element_mask = elements;
    s32 base_shift;

    requested_bonus = power_bonus;
    bonus = requested_bonus;
    affinity = 0;
    if ((target != 0) && (try_trigger_target_record_effect(target, (u16) element_mask, source_flags) == 0)) {
        if (requested_bonus == 0xFF) {
            bonus = ((S_8009CE1C_0 *)(((u8 *)dungeon_actor_ring_anchor)))->unk_11 * 4;
            if (bonus >= 0x64) {
                bonus = 0x63;
            }
            {
                s32 scaled_base_shift;
                scaled_base_shift = base << 0x10;
                base_shift = scaled_base_shift;
            }
        } else {
            s32 fixed_base_shift;
            fixed_base_shift = base << 0x10;
            base_shift = fixed_base_shift;
        }
        power = ((base_shift >> 0x10) + bonus) * 2;
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_7E = hit_angle;
        if ((((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_27 != 0)
            && !(((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30 & 0x238)
            && !(((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_5A & 0x8000)) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3E = (u16) (hit_angle + 0x800);
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3B
            + clamp_adjusted_value_0_to_99(target));
        if ((get_entity_effect_value(target, 0xA) << 0x10) != 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) ((s32) (((S_8009CE1C_1 *)((u8 *)target
                - 0x14))->unk_36.s << 0x10) >> 0x11);
        }
        if (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.u == 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)target
                - 0x14))->unk_36.s + 1);
        }
        target_elements = get_masked_record_flags(target, 7, 0);
        if (element_mask & 1) {
            if ((get_entity_effect_value(target, 0x13) << 0x10) != 0) {
                power >>= 2;
            } else {
                if (target_elements & 4) {
                    affinity += 1;
                }
                if (target_elements & 2) {
                    affinity -= 1;
                }
            }
        }
        if (element_mask & 2) {
            if ((get_entity_effect_value(target, 0x14) << 0x10) != 0) {
                power >>= 2;
            } else {
                if (target_elements & 1) {
                    affinity += 1;
                }
                if (target_elements & 4) {
                    affinity -= 1;
                }
            }
        }
        if (element_mask & 4) {
            if ((get_entity_effect_value(target, 0x12) << 0x10) != 0) {
                power >>= 2;
            } else {
                if (target_elements & 2) {
                    affinity += 1;
                }
                if (target_elements & 1) {
                    affinity -= 1;
                }
            }
        }
        affinity_shift = affinity << 0x10;
        affinity_product = power * (affinity_shift >> 0x10);
        /*
         * Possible original bug: only negative affinity products are divided by four. A +1 affinity doubles power
         * instead of adding the quarter suggested by the negative branch.
         */
        affinity_adjust = affinity_product;
        if (affinity_product < 0) {
            affinity_adjust = (s16) ((u32) (affinity_product + 3) >> 2);
        }
        power += affinity_adjust;
        damage_delta = (s32) ((s16) ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s - power) / 2;
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_78.s = (u16) damage_delta;
        if ((s16) damage_delta >= 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_78.u = -1;
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30 = (s32) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30
            | 0x20000000);
        if ((get_entity_effect_value(target, 0x1D) << 0x10) == 0) {
            shown_damage = (s16) (0 - ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_78.s);
        } else {
            shown_damage = 0;
        }
        create_actor_value_popup(3, target, shown_damage, 0);
        if (target == ((u8 *)dungeon_actor_ring_anchor)) {
            pending_player_damage_kind = (u8) hit_kind;
            clear_player_linked_action_flags();
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_74 = source_flags;
        g_dungeon_status.pending_display_owner = target - 0x20;
        if (!(((SpriteFrameState *)((S_8009CE1C_3_pre *)target)[-1].unk_00)->flags & 0x8000)) {
            initialize_timed_motion_step(8, 0x10);
        }
        event_id = 0x601;
        if ((source_flags != 0) && !(source_flags & 0x20000000)) {
            event_id = 0x602;
        }
        play_sound_if_enabled(event_id);
        position = ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_00;
        direction_offset = ((u16) ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3E >> 8) & 0xE;
        transition_effect_halfwords(
            (u16) ((position->unk_24 << 6) + ((dir_step_x[(u32) direction_offset >> 1] * 0x20) + 0x20)),
            (u16) ((position->unk_25 << 6) + ((dir_step_y[(u32) direction_offset >> 1] * 0x20) + 0x20)),
            (s16) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_9C - 0x30),
            element_mask, (s32) (s16) hit_angle);
    }
}
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_800287A4.h"

s32 get_entity_effect_value();                 /* extern */
s32 generate_random_value(void); /* Retail RNG at 0x800A6D30 reads no argument registers, including $a3. */
void *create_owner_linked_pulsing_effect();

typedef struct S_8009D218_1_pre {
    s32 unk_00;
    u8 pad_04[0x14];
} S_8009D218_1_pre;   /* the 0x18 bytes before entity in try_trigger_target_record_effect, addressed as entity[-1] */

/* extern */

/* Tests actor effects and a linked item chance, creating a pulsing effect and returning 1 when an
   effect is triggered. */
s32 try_trigger_target_record_effect(ActorRecord *entity, s32 flags, Rec_D_800287A4 *record) {
    u8 *value_ptr;

    if (!(flags & 8) && (record != NULL)) {
        if (flags & 1) {
            if (((get_entity_effect_value(entity, 0x16) << 0x10) != 0) && (record->unk_13 >= 0)) {
                create_owner_linked_pulsing_effect(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                return 1;
            }
        } else if (flags & 2) {
            if ((((get_entity_effect_value(entity, 0x16) << 0x10) != 0) || ((get_entity_effect_value(entity, 0x17) << 0x10) != 0))
                && (record->unk_13 >= 0)) {
                create_owner_linked_pulsing_effect(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                return 1;
            }
        } else if ((flags & 4) && (((get_entity_effect_value(entity, 0x16) << 0x10) != 0) || ((get_entity_effect_value(entity, 0x15) << 0x10)
            != 0)) && (record->unk_13 >= 0)) {
            create_owner_linked_pulsing_effect(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
            return 1;
        }
        {
            if (record != NULL) {
                value_ptr = (*(u8 * *)&entity->unk_50);
                if (value_ptr != NULL) {
                    if ((*value_ptr == 3) && (record->unk_13 >= 0) && (generate_random_value() & 3)) {
                                                /* Duplicate return node #22. Try simplifying control flow for better match */
                        create_owner_linked_pulsing_effect(((S_8009D218_1_pre *)entity)[-1].unk_00, entity, record);
                        return 1;
                    }
                                        /* Duplicate return node #25. Try simplifying control flow for better match */
                    return 0;
                }
                return 0;
            }
                        /* Duplicate return node #25. Try simplifying control flow for better match */
            return 0;
        }
    }
    return 0;
}

/* MECHANISM (byte-exact @ 2.7.2, dungeon overlay)
 * 1. IMPLICIT $a0 PASSTHROUGH: the first get_entity_effect_value site is spelled
 *    get_entity_effect_value(entity, 0x16) like the other three -- NOT m2c's one-arg
 *    get_entity_effect_value((void*)0x16). It sits in the ENTRY extended basic block, so
 *    cse still knows $a0 == entity and deletes the `move a0,s0` copy; retail's
 *    jal delay slot therefore carries `addiu a1,zero,0x16` (word 13) while the
 *    three later sites (all branch targets, cse reset) keep their `move a0,s0`.
 * 2. LEAD-22 SHAPE-C TAIL: func_8009D368 is declared VOID and the arm is spelled
 *    as two plain calls + a bare `return 1;` (never `return func_8009D368();`).
 *    Both callees are in config/sibcall_syms.dungeon.txt, so maspsx rewrites the
 *    shared-epilogue jal->j and relocates `addiu v0,zero,1` into the converted
 *    `j func_8009D368` delay slot (word 82) -- the func_800C7C24 spelling.
 * 3. ONE-SIDED ASM_MEM_BARRIER after the FIRST `return func_8009D34C();` arm
 *    defeats -O2 cross-jump merging of the two identical `j 8009d34c; nop` tail
 *    sites (words 21 and 39) so both survive; the flags&4 arm's `bgez -> 7bec`
 *    keeps the two create_owner_linked_pulsing_effect/func_8009D368 tails legitimately merged.
 */
#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"

extern void zero_words(int *dst, int count);          /* extern */
void update_packed_map_levels();                            /* extern */

/* Process the 0x200-byte global buffer and run the follow-up routine. */
void process_global_buffer_and_submit(void) {
    zero_words(packed_tile_heights, 0x200);
    update_packed_map_levels();
}
#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

/* Update packed map levels for the current region or neighboring tiles, then submit the map. */
void update_packed_map_levels(void) {
    TransitionWords map_params;
    MapGrid *grid;
    TileObject *obj;
    DungeonRoom *room;
    MapTile *tile;
    u8 *cell;
    s32 index;
    s16 level;
    s32 lv;
    u8 packed;
    s16 x;
    s16 y;
    s16 n;   /* the room scan's x end, then the neighbour scan's direction */
    s16 y_end;
    GameWork *gw;

    map_params = tile_height_upload_rect;
    gw = &g_game_work;
    grid = &gw->map;
    obj = &reference_tile_object;
    if (obj->room_index >= 0) {
        room = &dungeon_rooms[obj->room_index];
        y = room->y - 1;
        n = room->x + room->w + 1;
        y_end = room->h + y + 2;
        for (; y < y_end; y++) {
            for (x = room->x - 1; x < n; x++) {
                index = (y << grid->shiftX) + x;
                tile = &D_800EA000[index];
                if (tile->type != 0 && tile->type != 3) {
                    cell = &packed_tile_heights[index / 2];
                    level = (s16)(tile->height + 0x200) / 64;
                    if (level >= 16) {
                        level = 15;
                    } else if (level <= 0) {
                        level = 1;
                    }
                    lv = level;
                    packed = *cell;
                    if (x & 1) {
                        *cell = packed | (lv << 4);
                    } else {
                        *cell = packed | lv;
                    }
                }
            }
        }
    } else {
        for (n = 7; n >= 0; n--) {
            x = reference_tile_object.tile_position.parts.tile_x + dir_step_x[n];
            y = reference_tile_object.tile_position.parts.tile_y + dir_step_y[n];
            index = (y << grid->shiftX) + x;
            tile = &D_800EA000[index];
            if (tile->type != 0 && tile->type != 3) {
                cell = &packed_tile_heights[index / 2];
                level = (s16)(tile->height + 0x200) / 64;
                if (level >= 16) {
                    level = 15;
                } else if (level <= 0) {
                    level = 1;
                }
                lv = level;
                packed = *cell;
                if (x & 1) {
                    *cell = packed | (lv << 4);
                } else {
                    *cell = packed | lv;
                }
            }
        }
    }
    func_800672D8(&map_params, packed_tile_heights);
}
#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"

typedef struct S_8009D6F4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8009D6F4_1;   /* ((((row << shift) + col) * 6) + table) in refresh_packed_grid_nibbles */

typedef struct S_8009D6F4_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
} S_8009D6F4_0;

/* Refresh nonzero packed grid nibbles from clamped table values, then pass on the saved data. */
void refresh_packed_grid_nibbles(void) {
    TransitionWords saved_data;
    TransitionWords *data_source;
    register u8 *base;
    u8 *cursor;
    u8 *state;
    u8 *grid_dims;
    register u8 *table;
    s32 first_col;
    s32 dimension_unit;
    s16 next_row;
    s16 row_index;
    s32 row;
    u8 packed_output;
    u8 packed_input;

    data_source = &tile_height_upload_rect;
    saved_data = *data_source;
    packed_input = 0;
    base = packed_tile_heights;
    cursor = base;
    row_index = 0;
    state = ((u8 *)(&g_game_work));
    grid_dims = state + 0x1DC;
    if ((1 << ((S_8009D6F4_0 *)grid_dims)->unk_16) > 0) {
        s32 col_index;
        s32 nibble_mask;
        s32 next_col;

        first_col = 0;
        dimension_unit = 1;
        table = (u8 *)D_800EA000;
        do {
            col_index = 0;
            if (first_col < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14)) {
                nibble_mask = row_index << 16;
                row = nibble_mask >> 16;
                do {
                    nibble_mask = col_index & 1;
                    if (nibble_mask == 0) {
                        packed_input = *cursor;
                        *cursor = 0;
                        nibble_mask = packed_input & 0xF;
                    } else {
                        nibble_mask = packed_input & 0xF0;
                    }
                    if (nibble_mask != 0) {
                        s32 value_bits;
                        s32 value_bits_2;
                        s32 level;
                        s16 clamped_level;
                        s32 col;
                        register s16 shift;

                        col = (s16) col_index;
                        shift = ((S_8009D6F4_0 *)grid_dims)->unk_14;
                        value_bits_2 = (s16) (((S_8009D6F4_1 *)(((((row << shift) + col) * 6) + table)))->unk_02 + 0x200) / 64;
                        clamped_level = value_bits_2;
                        level = value_bits_2;
                        if (level >= 0x10) {
                            clamped_level = 15;
                        } else {
                            if (level <= 0) {
                                clamped_level = 1;
                            }
                        }
                        value_bits = clamped_level << 0x10;
                        level = value_bits >> 0x10;
                        packed_output = *cursor;
                        if (col_index & 1) {
                            value_bits = packed_output | (level << 4);
                        } else {
                            value_bits = packed_output | level;
                        }
                        *cursor = value_bits;
                    }
                    if (col_index & 1) {
                        next_col = col_index + 1;
                        cursor += 1;
                        col_index = next_col;
                    } else {
                        next_col = col_index + 1;
                        col_index = next_col;
                    }
                } while ((s16) next_col < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_14));
            }
            next_row = row_index + 1;
            row_index = next_row;
        } while (next_row < (dimension_unit << ((S_8009D6F4_0 *)grid_dims)->unk_16));
    }
    func_800672D8(&saved_data, base);
}
#include "modules/dungeon_engine_transition_effects_fragment_b7c20.h"
#include "common.h"
#include "shared/game_work.h"

typedef struct {
    u8 pad0[0x14];
    s16 field_14;
    s16 field_16;
} DungeonConfig;

extern void create_type_212_object(s32 flag, s8 value);

/* Pack dungeon cell height levels into nibbles and submit the buffer. */
void pack_and_submit_cell_height_levels(void) {
    TransitionWords upload_pair;
    DungeonConfig *config;
    u8 *dungeon_data;
    u8 *buffer;
    u8 *write_ptr;
    u8 *cells;
    u8 *cell;
    s32 zero;
    s32 one;
    s32 width_shift;
    s16 row;
    s32 column;
    s16 next_row;
    s32 row_offset;
    s32 level;
    u16 cell_type;
    s32 packed_levels;
    u8 packed_empty;
    s32 value;
    s32 value_2;

    upload_pair = tile_height_upload_rect;
    buffer = packed_tile_heights;
    write_ptr = buffer;
    dungeon_data = ((u8 *)(&g_game_work));
    config = (DungeonConfig *)(dungeon_data + 0x1DC);
    row = 0;
    if ((1 << config->field_16) > 0) {
        zero = 0;
        one = 1;
        cells = (u8 *)D_800EA000;
        do {
            column = 0;
            {
                s32 first_width_shift = config->field_14;
                u16 stride_shift;
                s32 row_index;
                stride_shift = config->field_14;
                if (zero < (one << first_width_shift)) {
                    row_index = row;
                    row_index = (s16)row_index;
                    row_offset = row_index << stride_shift;
                    while (1) {
                        row_offset += (s16) column;
                        cell = (u8 *)((long)(row_offset * 6) + (long)cells);
                        cell_type = *(u16 *)cell;
                        if ((cell_type != 0) && (cell_type != 3)) {
                            s16 raw_level;

                            value = (s16) (*(u16 *)(cell + 2) + 0x200) / 64;
                            stride_shift = value;
                            raw_level = value;
                            if (raw_level >= 0x10) {
                                stride_shift = 15;
                            } else if (raw_level <= 0) {
                                stride_shift = 1;
                            }
                            value = (u32) stride_shift << 16;
                            level = value >> 16;
                            packed_levels = *write_ptr;
                            if ((s32) column & 1) {
                                value = packed_levels | (level << 4);
                                *write_ptr = value;
                            } else {
                                value = packed_levels | level;
                                *write_ptr = value;
                            }
                        } else {
                            register s32 odd_column;

                            packed_empty = *write_ptr;
                            odd_column = column & 1;
                            if (odd_column) {
                                value = packed_empty & 0xF;
                            } else {
                                value = packed_empty & 0xF0;
                            }
                            *write_ptr = value;
                        }
                        {
                            s32 odd_column;
                            odd_column = column & 1;
                            if (odd_column) {
                                write_ptr += 1;
                                value_2 = column + 1;
                            } else {
                                value_2 = column + 1;
                            }
                        }
                        column = value_2;
                        value_2 = (u32)value_2 << 16;
                        value_2 >>= 16;
                        width_shift = config->field_14;
                        stride_shift = config->field_14;
                        width_shift = one << width_shift;
                        if (value_2 >= width_shift) {
                            break;
                        }
                        row_offset = row_index << stride_shift;
                    }
                }
            }
            next_row = row + 1;
            row = next_row;
            value_2 = (u32)next_row << 16;
            value_2 >>= 16;
            width_shift = config->field_16;
            width_shift = one << width_shift;
        } while (value_2 < width_shift);
    }
    func_800672D8(&upload_pair, buffer);
    create_type_212_object(1, 0x20);
}
