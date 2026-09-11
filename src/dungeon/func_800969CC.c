/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0

s32 func_8003AD08();
void func_800419EC();
s32 func_80042900();
M2C_UNK func_80094E34();
s32 func_80098250();
s32 func_800990FC();
s32 func_80099194();
M2C_UNK func_80099290();
s32 func_8009929C();
s32 func_8009955C();
s32 func_80099734();
M2C_UNK func_80099C58();
M2C_UNK func_8009BF7C();
M2C_UNK func_8009BFF8();
s32 func_8009CD58();
M2C_UNK func_800A2D68();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5720();
M2C_UNK func_800B4C7C();
s16 func_800B5ED0();
M2C_UNK func_800C7DEC();
s32 func_800C82B8();
extern s16 D_8006CCD8[8];
extern s16 D_8006CCE8[8];
extern void *D_80083470[3];
extern M2C_UNK D_800E0D7B;
extern M2C_UNK D_800E0D92;
extern M2C_UNK D_800E0D9E;
extern M2C_UNK D_800E0DB8;
extern M2C_UNK D_800E0DD0;
extern M2C_UNK D_800E0DDD;
extern M2C_UNK D_800E0DEA;
extern M2C_UNK D_800E3648;
extern void *D_800E3D7C[3];


typedef struct S_8009C12C_0 {
    u8 pad_00[0x13];
    s8 unk_13;
    union { s32 s32; u16 u16; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s32 unk_1C;
    union { u16 n; volatile u16 v; } unk_20;   /* accessed as both */
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
} S_8009C12C_0;   /* arg0 in func_8009C12C */

typedef struct S_8009C12C_1 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_8009C12C_1;   /* entry_page in func_8009C12C */

typedef struct S_8009C12C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8009C12C_2;   /* arg1 in func_8009C12C */

typedef struct S_8009C12C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009C12C_3_pre;   /* the 0x14 bytes before temp_s1 in func_8009C12C, addressed as temp_s1[-1] */

typedef struct S_8009C12C_3 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x2];
    union { u16 n; volatile u16 v; s16 n2; } unk_22;   /* accessed as both */
    u8 pad_24[0x3];
    u8 unk_27;
    u8 pad_28[0x38];
    void * unk_60;
    union { s16 n; volatile s16 v; } unk_64;   /* accessed as both */
    u8 pad_66[0x22];
    u16 unk_88;
} S_8009C12C_3;   /* temp_s1 in func_8009C12C */

typedef struct S_8009C12C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x3D66];
    void * unk_3D7C;
} S_8009C12C_4;   /* temp_ptr in func_8009C12C */

typedef struct S_8009C12C_5 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_8009C12C_5;   /* (void *)var_s0 in func_8009C12C */

typedef struct S_8009C12C_6 {
    u8 pad_00[0x3470];
    void * unk_3470;
} S_8009C12C_6;   /* var_v1 in func_8009C12C */

typedef struct S_8009C12C_7 {
    u8 pad_00[0x88];
    u16 unk_88;
} S_8009C12C_7;   /* table_v0 in func_8009C12C */

/* Resolve an attack against the linked target and display its damage and effects. */
void *func_8009C12C(void *attacker_in, void *tile_in, s16 direction, s16 distance) {
    S_8009C12C_2 *tile = tile_in;
    s16 tile_result;
    s16 height_diff;
    s32 damage;
    s16 message_state;
    s32 direction_offset;
    s32 target_flags;
    register s32 target_elements ASM_REG("$19");
    register s32 attack_elements ASM_REG("$23");
    register s32 message_start ASM_REG("$21");
    s32 attack_bonus;
    s8 attacker_kind;
    s32 half_delta;
    s32 attacker_blocked;
    s32 quarter_delta;
    register s32 opposite_offset ASM_REG("$3");
    s32 effect_elements;
    u32 effect_flags;
    register s32 message_cursor ASM_REG("$16");
    register s32 modifier ASM_REG("$18");
    s32 element_match;
    s32 element_check;
    register s32 scaled_modifier ASM_REG("$2");
    s32 signed_value;
    u16 *attack_script;
    u16 target_traits;
    register u8 kind_check ASM_REG("$4");
    S_8009C12C_4 *target_data;
    register s16 *opposite_x_ptr ASM_REG("$5");
    register s16 *direction_ptr ASM_REG("$2");
    register u16 direction_value ASM_REG("$12");
    register s32 effect_x ASM_REG("$4");
    register s32 step_distance ASM_REG("$9");
    s32 x_offset;
    register s32 y_step ASM_REG("$10");
    register s32 x_step ASM_REG("$11");
    s32 effect_y;
    register s32 zero ASM_REG("$0");
    struct {
        volatile u16 arg2;
        u8 gap[6];
        u16 arg3;
    } homes;
    register void **actor_page ASM_REG("$3");
    void *target;
    void *blocked_actor;
    void *null_result;

    modifier = 0;
#ifdef NON_MATCHING
    zero = 0;
#endif
    ((S_8009C12C_0 *)attacker_in)->unk_73 = 0;
    ASM_KEEP(tile);
    ((S_8009C12C_0 *)attacker_in)->unk_72 = 0;
    ASM_KEEP(direction);
    homes.arg2 = direction;
    target = ((S_8009C12C_0 *)attacker_in)->unk_60;
    message_state = modifier;
    homes.arg3 = distance;
    if (target == NULL) {
        S_8009C12C_1 *entry_page;
        entry_page = (void *)0x800E0000;
        null_result = NULL;
        if (attacker_in == entry_page->unk_3D7C) {
            tile_result = func_800B5ED0(tile->unk_24, tile->unk_25, direction, ((S_8009C12C_0 *)attacker_in)->unk_88);
            null_result = NULL;
            if (tile_result >= 0) {
                s32 tile_text;
                s32 tile_text_base;
                s32 tile_message;
                message_start = func_800990FC();
                tile_message = func_8009929C(8, message_start);
                tile_text = tile_result << 2;
                tile_text_base = (s32)&D_800E3648;
                tile_text += tile_text_base;
                tile_message = func_8009955C(tile_text, tile_message);
                tile_message = func_80099194(&D_800E0D7B, tile_message);
                func_80099290(tile_message);
                func_800A5720(message_start);
                func_800A56E0(0x700);
                func_800A2D68(attacker_in, 8);
                func_800B4C7C(0x82, attacker_in, 8, 1);
            }
        }
        return NULL;
    }
    message_start = func_800990FC();
    message_cursor = message_start;
    attacker_kind = ((S_8009C12C_0 *)attacker_in)->unk_13;
    kind_check = *(volatile u8 *)((s8 *)attacker_in + 0x13);
    if (attacker_kind >= 0) {
        target_data = ((S_8009C12C_3_pre *)target)[-1].unk_00;
        target_traits = target_data->unk_14;
        if (!(tile->unk_14 & target_traits & 0x8000) || ((kind_check == 0x23) && (((S_8009C12C_0 *)attacker_in)->unk_A6 != 0) && !(target_traits & 0x8000))) {
            message_cursor = func_8009929C(0xA, func_80099194(&D_800E0D92, func_80099734(attacker_in, message_start)));
        } else {
            attacker_blocked = ((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x4000;
            if ((attacker_blocked != 0) || (message_state = -1, ((((S_8009C12C_3 *)target)->unk_14 & 0x4000) != 0))) {
                blocked_actor = target;
                if (attacker_blocked != 0) {
                    blocked_actor = attacker_in;
                }
                message_cursor = func_80099194(&D_800E0D9E, func_80099734(blocked_actor, message_cursor));
                message_state = 1;
            }
        }
    }
    ((S_8009C12C_3 *)target)->unk_14 = (s32) (((S_8009C12C_3 *)target)->unk_14 | 0x01000000);
    if (((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x04000000) {
        func_800B4C7C(3, target, -1, 0);
        if (((S_8009C12C_0 *)attacker_in)->unk_13 >= 0) {
            signed_value = message_state << 16;
            modifier = signed_value >> 16;
            if (modifier == 0) {
                message_cursor = func_80099194(&D_800E0DB8, func_80099734(target, message_cursor));
            }
            null_result = NULL;
            if (modifier >= 0) {
                func_80099290(message_cursor);
                func_800A5720(message_start);
                return (void *)zero;
            }
            return null_result;
        }
        return (void *)zero;
    }
    attack_script = ((S_8009C12C_0 *)attacker_in)->unk_4C;
    if ((attack_script != NULL) && (*attack_script == 0xF0D)) {
        ((S_8009C12C_3 *)target)->unk_22.n = ((S_8009C12C_3 *)target)->unk_27;
    } else {
        ((S_8009C12C_3 *)target)->unk_22.v = (u16) (((S_8009C12C_3 *)target)->unk_27 + func_80098250(target));
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
    attack_elements = func_8009CD58(attacker_in, 7, 1);
    target_elements = func_8009CD58(target, 7, 0);
    if (attack_elements & 1) {
        if ((func_80042900(target, 0x13) << 0x10) != 0) {
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10) >> 0x12);
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
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10) >> 0x12);
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
            ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16) ((s32) (((S_8009C12C_0 *)attacker_in)->unk_20.n << 0x10) >> 0x12);
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
        register s32 element_product ASM_REG("$12");
        u16 attack_raw;
        void *bonus_actor;
        attack_value = (s16)((S_8009C12C_0 *)attacker_in)->unk_20.n;
        ASM_KEEP(attack_value);
        element_product = attack_value * (scaled_modifier >> 0x10);
        bonus_actor = attacker_in;
        attack_raw = ((S_8009C12C_0 *)attacker_in)->unk_20.v;
        ASM_KEEP4(bonus_actor, attack_raw, element_product, attack_value);
        attack_value = element_product >> 3;
        ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16)(attack_raw + attack_value);
        attack_bonus = func_800C82B8(bonus_actor);
    }
    if (attack_bonus != 0) {
        u16 bonus_base;
        register s32 bonus_scale ASM_REG("$2");
        register s32 bonus_product ASM_REG("$12");
        bonus_base = ((S_8009C12C_0 *)attacker_in)->unk_20.n;
        bonus_scale = (s32)(bonus_base << 0x10) >> 0x13;
        bonus_product = bonus_scale * attack_bonus;
        ((S_8009C12C_0 *)attacker_in)->unk_20.n = (u16)(bonus_base + bonus_product);
    }
    if (((S_8009C12C_0 *)attacker_in)->unk_1C & 0x01000000) {
        half_delta = (s32) ((s16) ((S_8009C12C_3 *)target)->unk_22.n - (s16) ((S_8009C12C_0 *)attacker_in)->unk_20.n) / 2;
        quarter_delta = (s32) ((s16) half_delta + ((u32) (half_delta << 0x10) >> 0x1F)) >> 1;
        ((S_8009C12C_3 *)target)->unk_64.n = (s16) (half_delta + quarter_delta);
    } else {
        ((S_8009C12C_3 *)target)->unk_64.v = (s16) ((s32) ((s16) ((S_8009C12C_3 *)target)->unk_22.n - (s16) ((S_8009C12C_0 *)attacker_in)->unk_20.n) / 2);
    }
    if (((S_8009C12C_3 *)target)->unk_64.n >= 0) {
        ((S_8009C12C_3 *)target)->unk_64.n = -1;
    }
    modifier = func_80042900(target, 0x1D);
    signed_value = message_state << 0x10;
    if (signed_value == 0) {
        message_cursor = func_80099734(target, message_cursor);
        {
            void *attack_text;
            if (((S_8009C12C_0 *)attacker_in)->unk_14.s32 & 0x2000) {
                attack_text = (void *)0x800E0000;
                ASM_KEEP(attack_text);
                attack_text += 0xDD0;
            } else {
                attack_text = &D_800E0DDD;
            }
            message_cursor = func_80099194(attack_text, message_cursor);
        }
        {
            s32 display_damage;
            s32 damage_message;
            if ((modifier << 0x10) != 0) {
                display_damage = 0;
                damage_message = message_cursor;
            } else {
                display_damage = ((S_8009C12C_3 *)target)->unk_64.n;
                damage_message = message_cursor;
                display_damage = 0 - display_damage;
            }
            message_cursor = func_8003AD08(display_damage, damage_message);
        }
        ASM_KEEP(message_cursor);
        message_cursor = func_80099194(&D_800E0DEA, message_cursor);
        ASM_KEEP(message_state);
        signed_value = message_state << 0x10;
    }
    if (signed_value >= 0) {
        func_80099290(message_cursor);
        func_800A5720(message_start);
    }
    {
        register u16 distance_raw ASM_REG("$12");
        register s32 signed_distance ASM_REG("$2");
        s32 one;
        distance_raw = *(volatile u16 *)&homes.arg3;
        one = 1;
        signed_distance = (s16)distance_raw;
        if (signed_distance == one) {
            func_800C7DEC(attacker_in, target);
        }
    }
    effect_flags = 0xDFFFFFFF;
    target_data = (void *)0x800E0000;
    ASM_KEEP_DEP_NV(target_data, effect_flags);
    target_flags = ((S_8009C12C_3 *)target)->unk_1C & effect_flags;
    target_data = target_data->unk_3D7C;
    ((S_8009C12C_3 *)target)->unk_1C = target_flags;
    if (target == target_data) {
        func_8009BFF8(target, attacker_in);
    }
    signed_value = modifier << 0x10;
    damage = 0;
    if (signed_value == 0) {
        signed_value = 0 - (u16) ((S_8009C12C_3 *)target)->unk_64.n;
        signed_value <<= 0x10;
        damage = signed_value >> 0x10;
    }
    func_800B4C7C(3, target, damage, 0);
    message_cursor = 0x800E0000;
    ASM_KEEP(message_cursor);
    actor_page = (void **)0x80080000;
    if (target == ((S_8009C12C_5 *)((void *)message_cursor))->unk_3D7C) {
        func_80094E34();
        actor_page = (void **)0x80080000;
    }
    ((S_8009C12C_3 *)target)->unk_60 = attacker_in;
    ((S_8009C12C_0 *)attacker_in)->unk_60 = target;
    ((S_8009C12C_6 *)actor_page)->unk_3470 = target - 0x20;
    if (((S_8009C12C_0 *)attacker_in)->unk_1C & 0x01000000) {
        register s32 effect_mode ASM_REG("$5");
        func_800A56E0(0x700);
        effect_flags = ((S_8009C12C_0 *)attacker_in)->unk_14.u16;
        effect_mode = 4;
        effect_flags &= 0x2000;
        effect_flags <<= 0x10;
        ASM_KEEP(effect_flags);
        effect_flags >>= 0x10;
        func_8009BF7C(effect_flags, effect_mode);
    }
    func_800A56E0(0x601);
    if (!(tile->unk_14 & 0x8000)) {
        func_800419EC(8, 0x10);
    }
    effect_elements = attack_elements << 0x10;
    if (attacker_in == ((S_8009C12C_5 *)((void *)message_cursor))->unk_3D7C) {
        if (((S_8009C12C_0 *)attacker_in)->unk_A8 != 0) {
            return target;
        }
    }
    effect_elements = attack_elements << 0x10;
    effect_elements >>= 0x10;
    opposite_x_ptr = (s16 *)0x80070000;
    ASM_KEEP(opposite_x_ptr);
    direction_value = homes.arg2;
    opposite_x_ptr = (s16 *)((s32)opposite_x_ptr - 0x3328);
    opposite_offset = (direction_value >> 9) & 7;
    direction_offset = opposite_offset * 2;
    direction_ptr = (s16 *)(direction_offset + (s32)opposite_x_ptr);
    ASM_KEEP(direction_ptr);
    opposite_offset = (opposite_offset + 4) & 7;
    opposite_offset *= 2;
    opposite_x_ptr = (s16 *)(opposite_offset + (s32)opposite_x_ptr);
    direction_value = homes.arg3;
    ASM_KEEP(direction_value);
    effect_x = *direction_ptr;
    direction_ptr = (s16 *)0x80070000;
    ASM_KEEP(direction_ptr);
    step_distance = (s16)direction_value;
    x_step = effect_x * step_distance;
    direction_ptr = (s16 *)((s32)direction_ptr - 0x3318);
    direction_offset += (s32)direction_ptr;
    opposite_offset += (s32)direction_ptr;
    x_offset = *opposite_x_ptr;
    effect_y = tile->unk_25;
    y_step = *(s16 *)direction_offset;
    direction_ptr = (s16 *)((S_8009C12C_0 *)attacker_in)->unk_60;
    opposite_offset = *(s16 *)opposite_offset;
    x_offset <<= 5;
    x_offset += 0x20;
    opposite_offset <<= 5;
    opposite_offset += 0x20;
    effect_x = tile->unk_24;
    direction_offset = ((S_8009C12C_7 *)direction_ptr)->unk_88 - 0x30;
    direction_offset = (s16)direction_offset;
    direction_ptr = (s16 *)(s32)((S_8009C12C_0 *)attacker_in)->unk_2A;
    effect_x += x_step;
    effect_x <<= 6;
    effect_x += x_offset;
    effect_x = (s16)effect_x;
    step_distance = y_step * step_distance;
    effect_y += step_distance;
    effect_y <<= 6;
    effect_y += opposite_offset;
    effect_y = (s16)effect_y;
    func_80099C58(effect_x, effect_y, direction_offset, effect_elements, (s32)direction_ptr);
    ASM_SET(y_step);
    return target;
}
