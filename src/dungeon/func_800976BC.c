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

typedef struct S_8009CE1C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009CE1C_4;   /* ((S_8009CE1C_3_pre *)arg0)[-1].unk_00 in apply_attack_power_and_element_effects */


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

typedef struct S_8009CE1C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009CE1C_2;


extern u8 D_800E3E41;
void clear_player_linked_action_flags(void);
s32 clamp_adjusted_value_0_to_99();
s32 func_8009CFB4();
s32 func_8009CFF4();
s32 func_8009D034();
extern s32 try_trigger_target_record_effect(EntityRec *entity, s32 flags, Rec_D_800287A4 *record);
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
    S_8009CE1C_2 *position;
    register u16 base = base_power;
    s16 element_mask = elements;
    s32 base_shift;

    requested_bonus = power_bonus;
    bonus = requested_bonus;
    affinity = 0;
    if ((target != 0) && (try_trigger_target_record_effect(target, (u16) element_mask, source_flags) == 0)) {
        if (requested_bonus == 0xFF) {
            bonus = ((S_8009CE1C_0 *)(((u8 *)D_800E3D7C)))->unk_11 * 4;
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
        if ((func_80042900(target, 0xA) << 0x10) != 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) ((s32) (((S_8009CE1C_1 *)((u8 *)target
                - 0x14))->unk_36.s << 0x10) >> 0x11);
        }
        if (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.u == 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)target
                - 0x14))->unk_36.s + 1);
        }
        target_elements = get_masked_record_flags(target, 7, 0);
        if (element_mask & 1) {
            if ((func_80042900(target, 0x13) << 0x10) != 0) {
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
            if ((func_80042900(target, 0x14) << 0x10) != 0) {
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
            if ((func_80042900(target, 0x12) << 0x10) != 0) {
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
        if ((func_80042900(target, 0x1D) << 0x10) == 0) {
            shown_damage = (s16) (0 - ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_78.s);
        } else {
            shown_damage = 0;
        }
        create_actor_value_popup(3, target, shown_damage, 0);
        if (target == ((u8 *)D_800E3D7C)) {
            D_800E3E41 = (u8) hit_kind;
            clear_player_linked_action_flags();
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_74 = source_flags;
        g_dungeon_status.unk_10 = target - 0x20;
        if (!(((S_8009CE1C_4 *)(((S_8009CE1C_3_pre *)target)[-1].unk_00))->unk_14 & 0x8000)) {
            func_800419EC(8, 0x10);
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
