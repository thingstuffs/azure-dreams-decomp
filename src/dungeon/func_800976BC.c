#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009CE1C_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8009CE1C_3_pre;   /* the 0x14 bytes before arg0 in func_8009CE1C, addressed as arg0[-1] */

typedef struct S_8009CE1C_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009CE1C_4;   /* ((S_8009CE1C_3_pre *)arg0)[-1].unk_00 in func_8009CE1C */


typedef struct S_8009CE1C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
} S_8009CE1C_0;   /* *D_800E3D7C in func_8009CE1C */

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
} S_8009CE1C_1;   /* arg0 in func_8009CE1C; pointer addresses record offset 0x14 */

typedef struct S_8009CE1C_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009CE1C_2;   /* temp_t1 in func_8009CE1C */


extern u8 *D_800E3D7C[];
extern u8 D_800E3E41;
extern void *D_80083470[3];
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];
M2C_UNK func_80094E34();
s32 func_80098250();
M2C_UNK func_8009CFB4();
M2C_UNK func_8009CFF4();
M2C_UNK func_8009D034();
s32 func_8009D218(void *, s32, s32);
M2C_UNK func_800A56E0();
M2C_UNK func_800B4C7C();
extern void func_80099C58(s16, s16, s16, s16, s32);

/* Compute elemental damage for a target and trigger its hit response. */
void func_8009CE1C(void *target, s16 base_power, s16 power_bonus, s16 elements,
                   u16 hit_angle, s32 source_flags, u16 hit_kind) {
    M2C_UNK event_id;
    s16 affinity_product;
    s32 shown_damage;
    s16 bonus;
    s16 affinity_adjust;
    s32 power;
    register s32 target_elements ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 damage_delta;
    M2C_UNK direction_offset;
    s32 affinity;
    register s16 requested_bonus ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 second_element;
    s32 third_element;
    M2C_UNK affinity_shift;
    register s32 first_affinity ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_8009CE1C_2 *position;
    register u16 base = base_power;
    register s16 element_mask ASM_REG("$21") = elements;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 base_shift;

    requested_bonus = power_bonus;
    bonus = requested_bonus;
    affinity = 0;
    if ((target != NULL) && (func_8009D218(target, element_mask & 0xFFFF, source_flags) == 0)) {
        if (requested_bonus == 0xFF) {
            bonus = ((S_8009CE1C_0 *)(*D_800E3D7C))->unk_11 * 4;
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
        ASM_USE_NV(requested_bonus);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        power = ((base_shift >> 0x10) + bonus) * 2;
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_7E = hit_angle;
        if ((((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_27 != 0) && !(((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30 & 0x238) && !(((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_5A & 0x8000)) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3E = (u16) (hit_angle + 0x800);
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3B + func_80098250(target));
        if ((func_80042900(target, 0xA) << 0x10) != 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) ((s32) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s << 0x10) >> 0x11);
        }
        if (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.u == 0) {
            ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s = (u16) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_36.s + 1);
        }
        target_elements = func_8009CD58(target, 7, 0);
        if (element_mask & 1) {
            if ((func_80042900(target, 0x13) << 0x10) != 0) {
                power >>= 2;
                goto check_second_element;
            }
            if (target_elements & 4) {
                affinity += 1;
            }
            if (target_elements & 2) {
                affinity -= 1;
                goto check_second_element;
            }
            second_element = element_mask & 2;
            goto apply_second_element;
        }
check_second_element:
        second_element = element_mask & 2;
apply_second_element:
        if (second_element != 0) {
            if ((func_80042900(target, 0x14) << 0x10) != 0) {
                power >>= 2;
                goto check_third_element;
            }
            if (target_elements & 1) {
                affinity += 1;
            }
            if (target_elements & 4) {
                affinity -= 1;
                goto check_third_element;
            }
            third_element = element_mask & 4;
            goto apply_third_element;
        }
check_third_element:
        third_element = element_mask & 4;
apply_third_element:
        if (third_element != 0) {
            if ((func_80042900(target, 0x12) << 0x10) != 0) {
                power >>= 2;
                goto scale_affinity;
            }
            if (target_elements & 2) {
                affinity += 1;
            }
            first_affinity = target_elements & 1;
            if (first_affinity) {
                affinity -= 1;
                goto scale_affinity;
            }
            affinity_shift = affinity << 0x10;
            goto apply_affinity;
        }
scale_affinity:
        affinity_shift = affinity << 0x10;
apply_affinity:
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
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30 = (s32) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_30 | 0x20000000);
        if ((func_80042900(target, 0x1D) << 0x10) == 0) {
            shown_damage = (s16) (0 - ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_78.s);
        } else {
            shown_damage = 0;
        }
        func_800B4C7C(3, target, shown_damage, 0);
        if (target == *D_800E3D7C) {
            D_800E3E41 = (u8) hit_kind;
            func_80094E34();
        }
        ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_74 = source_flags;
        D_80083470[0] = target - 0x20;
        if (!(((S_8009CE1C_4 *)(((S_8009CE1C_3_pre *)target)[-1].unk_00))->unk_14 & 0x8000)) {
            func_800419EC(8, 0x10);
        }
        event_id = 0x601;
        if ((source_flags != 0) && !(source_flags & 0x20000000)) {
            event_id = 0x602;
        }
        func_800A56E0(event_id);
        position = ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_00;
        direction_offset = ((u16) ((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_3E >> 8) & 0xE;
        func_80099C58(
            (u16) ((position->unk_24 << 6) + ((D_8006CCD8[(u32) direction_offset >> 1] * 0x20) + 0x20)),
            (u16) ((position->unk_25 << 6) + ((D_8006CCE8[(u32) direction_offset >> 1] * 0x20) + 0x20)),
            (s16) (((S_8009CE1C_1 *)((u8 *)target - 0x14))->unk_9C - 0x30),
            element_mask, (s32) (s16) hit_angle);
    }
}
