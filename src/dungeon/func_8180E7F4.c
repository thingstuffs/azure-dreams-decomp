/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

s16 func_8002773C();
void *func_800280F4(void *, void *, u16 *);
void func_8003DB4C();
M2C_UNK func_80041E70();
void func_80042710();
void func_80042984();
M2C_UNK func_80098B38();
M2C_UNK func_8009A028();
M2C_UNK func_8009A3D0();
M2C_UNK func_800A18E8();
s32 func_800A1BD0();
M2C_UNK func_800A31D0();
s16 func_800A57B4();
typedef struct {
    u8 pad_00[0x10];
    u8 flags;
    u8 pad_11[3];
} D_8006DE24_Record;
extern u8 D_80010980[];
extern u8 D_800287B4[];
extern s32 D_8006D6D8[4];
extern D_8006DE24_Record D_8006DE24[];
extern s32 D_800814A0;
extern void *D_800814A8;
extern void *D_800E3DF0[];
extern u8 D_800E3E48[];
extern u8 D_80080000[];
extern u8 D_80030000[];
__asm__(".set D_80080000, 0x80080000");
__asm__(".set D_80030000, 0x80030000");


typedef struct S_800277F4_0 {
    u8 pad_00[0xE];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    union { s32 n; volatile s32 v; } unk_14;   /* accessed as both */
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x4];
    union { struct { u16 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 pad_26[0x1D];
    u8 unk_43;
    s8 unk_44;
    u8 pad_45[0x3];
    union { struct { s32 v; } at00; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x3]; u8 v; } at03; } unk_48;   /* overlapping accesses */
    u8 pad_4C[0x8];
    s32 unk_54;
    u8 pad_58[0xE];
    u8 unk_66;
} S_800277F4_0;   /* var_s2 in func_800277F4 */

typedef struct S_800277F4_1 {
    s8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800277F4_1;   /* temp_v0_2 in func_800277F4 */

typedef struct S_800277F4_2 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_2;   /* temp_s0 in func_800277F4 */

typedef struct S_800277F4_3 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_3;   /* temp_a0_3 in func_800277F4 */

typedef struct S_800277F4_4 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
} S_800277F4_4;   /* temp_a0_5 in func_800277F4 */

typedef struct S_800277F4_5 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_5;   /* copy_src in func_800277F4 */

typedef struct S_800277F4_6 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_6;   /* temp_s1 in func_800277F4 */

typedef struct S_800277F4_7 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_7;   /* temp_a1_2 in func_800277F4 */

typedef struct S_800277F4_8_pre {
    void * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800277F4_8_pre;   /* the 0x14 bytes before var_s4 in func_800277F4, addressed as var_s4[-1] */

typedef struct S_800277F4_8 {
    u8 pad_00[0xE];
    u8 unk_0E;
    u8 pad_0F[0x4];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x4];
    u16 unk_24;
    u8 pad_26[0x1D];
    u8 unk_43;
    u8 pad_44[0x10];
    s32 unk_54;
} S_800277F4_8;   /* var_s4 in func_800277F4 */

typedef struct S_800277F4_9 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800277F4_9;   /* (var_a0 + temp_s1_2) in func_800277F4 */

typedef struct S_800277F4_10 {
    u8 pad_00[0x8];
    u8 unk_08;
} S_800277F4_10;   /* (var_v0_3 + temp_s1_2) in func_800277F4 */

typedef struct S_800277F4_11 {
    u8 pad_00[0xA];
    u8 unk_0A;
} S_800277F4_11;   /* temp_a1 in func_800277F4 */

typedef struct S_800277F4_12 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_12;   /* (var_v1 + temp_a0) in func_800277F4 */

typedef struct S_800277F4_13 {
    u8 unk_00;
    u8 pad_01[0x1];
    u8 unk_02;
} S_800277F4_13;   /* temp_a3 in func_800277F4 */

typedef struct S_800277F4_14 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_14;   /* fallback_source in func_800277F4 */

typedef struct S_800277F4_15 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800277F4_15;   /* temp_a0_8 in func_800277F4 */

typedef struct S_800277F4_16 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 pad_09[0x1];
    u8 unk_0A;
} S_800277F4_16;   /* (var_s2 + (var_s3 * 3)) in func_800277F4 */

typedef struct S_800277F4_17 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_800277F4_17;   /* slot_addr in func_800277F4 */

typedef struct S_800277F4_18 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800277F4_18;   /* temp_a0_9 in func_800277F4 */

typedef struct S_800277F4_19 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_800277F4_19;   /* runtime_addr in func_800277F4 */

typedef struct S_800277F4_20 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800277F4_20;   /* temp_s1_3 in func_800277F4 */

/* Merges two creatures' abilities and state, optionally copying the result and removing the donor. */
void *func_800277F4(void *first, void *second, void *destination) {
    u8 merge_buffer[17];
#define donor_seen (merge_buffer + 3)
#define merged_abilities (merge_buffer + 8)
    u16 merged_element;
    u16 ability_limit;
    s32 element_mask;
    u8 *clear_donor_seen;
    u8 *clear_result_seen;
    u8 *clear_abilities;
    u8 *ability_ids;
    D_8006DE24_Record *ability_table;
    u8 *result_seen;
    u8 *merge_out;
    u8 *other_data;
    M2C_UNK map_mask;
    s16 result_primary;
    s16 donor_primary;
    s16 result_match;
    s16 other_match;
    register s16 ability_count ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 source_side;
    s32 match_offset;
    s32 result_traits;
    s32 next_clear;
    register s32 donor_traits ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 donor_trait_bits;
    s32 ability_offset;
    s32 clear_shifted;
    s32 clear_slot;
    s32 ability_index;
    s32 allowed_elements;
    s32 slot_index;
    s32 slot_flags;
    register s32 global_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    s32 owner_action;
    s32 scan_index;
    register s32 clear_index ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *ability_data;
    u8 *slot_addr;
    u8 matched_ability;
    u8 ability_level;
    u8 result_kind;
    u8 level_cap;
    u8 donor_owner;
    u8 room_x;
    u8 room_y;
    u8 merge_key;
    register void *update_target ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    void *donor_ability;
    void *primary_output;
    void *merged_entry;
    void *donor_position;
    void *result_ability;
    void *fallback_output;
    void *result_primary_data;
    void *donor_primary_data;
    void *donor_runtime;
    void *clear_entry;
    void *source;
    void *other;
    void *result;
    register void *donor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *first_creature = first;
    s32 seen_mark;
    void *key_source;
    void *level_source;

    {
        register void *second_creature ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        second_creature = second;
        ability_limit = 2;
        result = func_800280F4(first_creature, second_creature, &merged_element);
        if (result == NULL) {
            return NULL;
        }
        {
            void *copy_target = destination;
            if (copy_target != NULL) {
                func_80042710(copy_target, result);
                if (first_creature == result) {
                    first_creature = destination;
                    result = first_creature;
                    goto select_donor;
                }
                second_creature = destination;
                result = second_creature;
            }
select_donor:
            donor = second_creature;
            if (first_creature != result) {
                donor = first_creature;
            }
        }
        clear_index = 2;
        clear_abilities = merged_abilities;
        clear_result_seen = merge_buffer;
        clear_donor_seen = donor_seen;
        element_mask = merged_element;
        clear_shifted = ((S_800277F4_0 *)result)->unk_14.n & ~7;
        ((S_800277F4_0 *)result)->unk_14.v = clear_shifted;
        clear_shifted |= element_mask;
        ((S_800277F4_0 *)result)->unk_14.n = clear_shifted;
        do {
            clear_shifted = clear_index << 0x10;
            next_clear = clear_index - 1;
            clear_index = next_clear;
            clear_slot = clear_shifted >> 0x10;
            clear_entry = clear_abilities + (clear_slot * 3);
            ((S_800277F4_1 *)clear_entry)->unk_00 = 0;
            ((S_800277F4_1 *)clear_entry)->unk_02 = 0;
            clear_donor_seen[clear_slot] = 0;
            clear_result_seen[clear_slot] = 0;
            ASM_KEEP_NV(next_clear);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        } while ((s16) next_clear >= 0);
        ability_count = 0;
        result_primary = func_8002773C(result, clear_donor_seen, clear_result_seen, clear_abilities);
        if (result_primary >= 0) {
#ifdef NON_MATCHING
            seen_mark = 1;
            merge_buffer[result_primary] = (u8) seen_mark;
#else
            {
                u8 *primary_seen_base =
                    (u8 *) &merged_element + result_primary - 0x28;

                seen_mark = 1;
                primary_seen_base[0x10] = (u8) seen_mark;
            }
#endif
            result_primary_data = result + (result_primary * 3);
            element_mask = (s16) func_800A57B4(donor, ((S_800277F4_2 *)result_primary_data)->unk_08);
            if (element_mask >= 0) {
                donor_seen[element_mask] = (u8) seen_mark;
                donor_ability = donor + (element_mask * 3);
                if ((u8) ((S_800277F4_2 *)result_primary_data)->unk_0A < (u8) ((S_800277F4_3 *)donor_ability)->unk_0A) {
                    primary_output = merged_abilities + (ability_count * 3);
                    ((S_800277F4_4 *)primary_output)->unk_00 = ((S_800277F4_3 *)donor_ability)->unk_08;
                    ((S_800277F4_4 *)primary_output)->unk_02 = ((S_800277F4_3 *)donor_ability)->unk_0A;
                    goto result_primary_done;
                }
            }
            {
                s32 copy_dst_index = (s16) ability_count;
                s32 copy_dst_offset;
                u8 *copy_dst;
                s32 copy_src_index;
                u8 *copy_src;

                copy_dst_offset = copy_dst_index * 3;
                ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                copy_dst = merged_abilities;
                ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                copy_src_index = (s16) result_primary;

                copy_src = result + (copy_src_index * 3);

                (*(u8 *)((u8 *)copy_dst + copy_dst_offset)) = (u8) ((S_800277F4_5 *)copy_src)->unk_08;
                (*(u8 *)((u8 *)copy_dst + copy_dst_offset + 2)) = (u8) ((S_800277F4_5 *)copy_src)->unk_0A;
            }
result_primary_done:
            ability_count += 1;
        }
merge_donor_primary:
        donor_primary = func_8002773C(donor);
        if (donor_primary >= 0) {
            register u8 *visited_slot ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
#ifdef NON_MATCHING
            visited_slot = donor_seen + donor_primary;
#else
            {
                u8 *frame_base =
                    (u8 *) &merged_element - 0x28;
                register u8 *visited_base ASM_REG("$2") =
                    frame_base + 0x13;
                visited_slot = visited_base + donor_primary;
            }
#endif
            ASM_KEEP_NV(visited_slot);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            if (*visited_slot == 0) {
                donor_primary_data = donor + (donor_primary * 3);
                result_match = func_800A57B4(result, ((S_800277F4_6 *)donor_primary_data)->unk_08);
                if (result_match >= 0) {
                    merge_buffer[result_match] = 1;
                }
                *visited_slot = 1;
                if (result_match >= 0) {
                    result_ability = result + (result_match * 3);
                    if ((u8) ((S_800277F4_6 *)donor_primary_data)->unk_0A < (u8) ((S_800277F4_7 *)result_ability)->unk_0A) {
                        s32 copy_dst_index = (s16) ability_count;
                        s32 copy_dst_offset;
                        u8 *copy_dst;

                        copy_dst_offset = copy_dst_index * 3;
                        ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        copy_dst = merged_abilities;

                        copy_dst += copy_dst_offset;
                        matched_ability = ((S_800277F4_7 *)result_ability)->unk_08;
                        (*(u8 *)((u8 *)copy_dst + 0)) = matched_ability;
                        (*(u8 *)((u8 *)copy_dst + 2)) = ((S_800277F4_7 *)result_ability)->unk_0A;
                        goto donor_primary_done;
                    }
                }
                {
                    s32 copy_dst_index = (s16) ability_count;
                    s32 copy_dst_offset;
                    u8 *copy_dst;
                    s32 copy_src_index;
                    register u8 *copy_src ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                    copy_dst_offset = copy_dst_index * 3;
                    ASM_KEEP_NV(copy_dst_offset);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                    copy_dst = merged_abilities;
                    ASM_KEEP_NV(copy_dst);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    copy_src_index = (s16) donor_primary;

                    copy_src = donor + (copy_src_index * 3);

                    copy_dst += copy_dst_offset;
                    (*(u8 *)((u8 *)copy_dst + 0)) = (u8) ((S_800277F4_5 *)copy_src)->unk_08;
                    (*(u8 *)((u8 *)copy_dst + 2)) = (u8) ((S_800277F4_5 *)copy_src)->unk_0A;
                }
donor_primary_done:
                ability_count += 1;
            }
        }
        {
            u16 merge_limit = 3;
            if ((((S_800277F4_0 *)result)->unk_0E != 0) || (((S_800277F4_8 *)donor)->unk_0E != 0)) {
                ability_limit = merge_limit;
                source_side = 0;
            } else {
                source_side = 0;
            }
        }
        scan_index = 0;
        result_seen = merge_buffer;
        ASM_KEEP_NV(result_seen);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        merge_out = merged_abilities;
        ASM_KEEP_NV(merge_out);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
scan_abilities:
        if (ability_count < (s32) ability_limit) {
            source = donor;
            if (source_side == 0) {
                source = result;
            }
            ability_index = scan_index >> 1;
            ability_offset = ability_index * 3;
            if ((((S_800277F4_9 *)((source + ability_offset)))->unk_08 != 0) && (*((source_side * 3) + result_seen + ability_index) == 0)) {
                other = donor;
                if (source_side != 0) {
                    other = result;
                }
                key_source = donor;
                if (source_side == 0) {
                    key_source = result;
                }
                merge_key = ((S_800277F4_10 *)((key_source + ability_offset)))->unk_08;
                other_match = func_800A57B4(other, merge_key);
                if (other_match < 0) {
                    clear_result_seen = donor;
                    goto copy_source_ability;
                }
                if (other_match >= 0) {
                    other_data = result_seen;
                    if (source_side == 0) {
                        other_data = donor_seen;
                    }
                    *(other_data + other_match) = 1;
                    level_source = donor;
                    if (source_side == 0) {
                        level_source = result;
                    }
                    other_data = donor;

                    ability_data = level_source + ability_offset;
                    if (source_side != 0) {
                        other_data = result;
                    }
                    match_offset = other_match * 3;
                    if ((u8) ((S_800277F4_11 *)ability_data)->unk_0A < (u8) ((S_800277F4_12 *)((other_data + match_offset)))->unk_0A) {
                        other_data = donor;
                        ability_data = merge_out + (ability_count * 3);
                        if (source_side != 0) {
                            other_data = result;
                        }
                        *ability_data = ((S_800277F4_12 *)((other_data + match_offset)))->unk_08;
                        other_data = donor;
                        if (source_side != 0) {
                            other_data = result;
                        }
                        ability_data[2] = ((S_800277F4_12 *)((other_data + match_offset)))->unk_0A;
                        goto finish_ability;
                    }
                    clear_result_seen = donor;
                    goto copy_source_ability;
                }
copy_source_ability:
                fallback_output = merge_out + (ability_count * 3);
                if (source_side == 0) {
                    clear_result_seen = result;
                }
                {
                    s32 fallback_index = scan_index >> 1;
                    s32 fallback_twice = fallback_index * 2;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                    s32 fallback_offset = fallback_twice + fallback_index;
                    u8 *fallback_source;
                    u8 *second_source;

                    fallback_source = clear_result_seen + fallback_offset;

                    ((S_800277F4_13 *)fallback_output)->unk_00 = ((S_800277F4_14 *)fallback_source)->unk_08;
                    second_source = donor;
                    if (source_side == 0) {
                        second_source = result;
                    }


                    ((S_800277F4_13 *)fallback_output)->unk_02 = ((S_800277F4_14 *)(second_source + fallback_offset))->unk_0A;
                }
finish_ability:
                merged_entry = merge_out + (ability_count * 3);
                if (((S_800277F4_15 *)merged_entry)->unk_00 == 0x2E) {
                    ((S_800277F4_15 *)merged_entry)->unk_00 = 0U;
                    ((S_800277F4_15 *)merged_entry)->unk_02 = 0;
                }
                ability_count += 1;
                {
                    u8 *visited_row = (u8 *) ((source_side * 3) + (s32) result_seen);
                    s32 visited_index = scan_index >> 1;
                    visited_row[visited_index] = 1;
                }
                goto next_ability;
            }
next_ability:
            scan_index += 1;
            source_side ^= 1;
            if (scan_index >= 6) {
                goto apply_abilities;
            }
            goto scan_abilities;
        }
apply_abilities:
        scan_index = 2;
        if ((ability_count << 0x10) == 0) {
            u8 *default_table = (u8 *) 0x80030000;
            s32 default_index;
            ASM_KEEP_NV(default_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            default_index = ((S_800277F4_0 *)result)->unk_13;
            ASM_KEEP(default_index);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            default_table -= 0x784C;
            ASM_KEEP_NV(default_table);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            default_index += (s32) default_table;
            merged_abilities[0] = *(u8 *) default_index;
            merged_abilities[2] = 1;
        }
        ASM_USE_NV(ability_count);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        ability_table = D_8006DE24;
        ability_ids = &merge_buffer[8];
        do {
            {
                register s32 ability_id ASM_REG("$2") = ability_ids[scan_index * 3];   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(ability_id);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                if (ability_id != 0) {
                    s32 ability = ability_id;
                    allowed_elements = ((S_800277F4_0 *)result)->unk_14.n;
                    if (!(ability_table[ability].flags & 7 & allowed_elements)) {
                        if (allowed_elements & 1) {
                            ability_ids[scan_index * 3] = (u8) ((((ability - 1) / 3) * 3) + 1);
                            goto store_ability;
                        }
                        if (allowed_elements & 2) {
                            ability_ids[scan_index * 3] = (u8) ((((ability - 1) / 3) * 3) + 2);
                            goto store_ability;
                        }
                        if (allowed_elements & 4) {
                            ability_ids[scan_index * 3] = (u8) ((((ability - 1) / 3) * 3) + 3);
                        }
                        goto store_ability;
                    }
                }
            }
store_ability:
            ((S_800277F4_16 *)((result + (scan_index * 3))))->unk_08 = (u8) ability_ids[scan_index * 3];
            ability_level = ability_ids[(scan_index * 3) + 2];
            ((S_800277F4_16 *)((result + (scan_index * 3))))->unk_0A = ability_level;
            scan_index -= 1;
        } while (scan_index >= 0);
        {
            s32 donor_kind = ((S_800277F4_8 *)donor)->unk_13;
            s32 base_kind = ((S_800277F4_0 *)result)->unk_13;
            s32 *donor_mask_ptr, *result_mask_ptr;
            s32 result_mask, base_traits;
            update_target = result;

            donor_traits = (s32) D_8006D6D8;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            donor_trait_bits = ((S_800277F4_8 *)donor)->unk_54;
            donor_mask_ptr = (s32 *) donor_traits + donor_kind;
            result_mask_ptr = (s32 *) donor_traits + base_kind;
            donor_traits = *donor_mask_ptr;
            base_traits = ((S_800277F4_0 *)result)->unk_54;
            result_mask = *result_mask_ptr;
            donor_traits &= donor_trait_bits;
            ((S_800277F4_0 *)result)->unk_54 = (s32) ((base_traits & result_mask) | donor_traits);
        }
        func_80041E70(update_target, donor_traits, donor_trait_bits);
        ((S_800277F4_0 *)result)->unk_24.at00.v = (u16) ((u32) ((((S_800277F4_0 *)result)->unk_24.at00.v + ((S_800277F4_8 *)donor)->unk_24) & 0xFFFF) >> 1);
        level_cap = ((S_800277F4_0 *)result)->unk_66;
        if (level_cap < (u8) ((S_800277F4_0 *)result)->unk_24.at01.v) {
            ((S_800277F4_0 *)result)->unk_24.at01.v = level_cap;
        }
        ((S_800277F4_0 *)result)->unk_24.at00u.v = 0xFF;
        if (((S_800277F4_0 *)result)->unk_24.at01.v != 0) {
            ((S_800277F4_0 *)result)->unk_1C = (s32) (((S_800277F4_0 *)result)->unk_1C & ~8);
        }
        if (destination == NULL) {
            func_80042984(result);
        }
        if ((((S_800277F4_0 *)result)->unk_48.at01.v != 0) && !(((S_800277F4_0 *)result)->unk_48.at03.v & 0x20)) {
            ((S_800277F4_0 *)result)->unk_48.at00.v = 0;
        }
        owner_action = 0;
        if ((u8) ((S_800277F4_0 *)result)->unk_43 < 0x40U) {
            owner_action = ((u8) ((S_800277F4_8 *)donor)->unk_43 < 0x40U) * 2;
        } else {
            donor_owner = ((S_800277F4_8 *)donor)->unk_43;
            if (donor_owner < 0x40U) {
                owner_action = 1;

                ((S_800277F4_0 *)result)->unk_43 = donor_owner;
                slot_index = owner_action;
                ((S_800277F4_0 *)result)->unk_44 = (s8) slot_index;
            }
        }
        if (destination == NULL) {
            func_800A31D0(donor);
            func_800A18E8(((S_800277F4_8 *)donor)->unk_13, 3);
            slot_index = func_800A1BD0(donor);
            {
#ifdef NON_MATCHING
                u8 *slot_page = D_80080000;
#else
                u8 *slot_page = (u8 *) 0x80080000;
#endif
                ASM_KEEP_NV(slot_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                element_mask = *(u8 **) (slot_page + 0x14A8);
            }
            slot_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) element_mask);
            ASM_KEEP_NV(slot_addr);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

            slot_flags = ((S_800277F4_8 *)donor)->unk_1C & 0x2000;
            donor_position = ((S_800277F4_8_pre *)donor)[-1].unk_00;
            donor_runtime = ((S_800277F4_17 *)slot_addr)->unk_D0;
            room_x = ((S_800277F4_18 *)donor_position)->unk_24;
            room_y = ((S_800277F4_18 *)donor_position)->unk_25;
            ASM_KEEP(slot_flags);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            map_mask = 0x3000;
            if (slot_flags != 0) {
                map_mask = 0x300;
            }
            func_8009A3D0(room_x, room_y, map_mask);
            func_8009A028(donor);
            if (owner_action == 1) {
#ifdef NON_MATCHING
                D_80010980[((S_800277F4_8 *)donor)->unk_43 * 4] = ((S_800277F4_0 *)result)->unk_13;
#else
                u8 *room_page = (u8 *) 0x80010000;

                room_page[0x980 + (((S_800277F4_8 *)donor)->unk_43 * 4)] = ((S_800277F4_0 *)result)->unk_13;
#endif
                ((S_800277F4_8 *)donor)->unk_43 = 0xFF;
            } else if (owner_action == 2) {
#ifdef NON_MATCHING
                *(s32 *) &D_80010980[((S_800277F4_8 *)donor)->unk_43 * 4] = 0;
#else
                u32 room_base = 0x80010000;
                s32 room_index;
                room_index = ((S_800277F4_8 *)donor)->unk_43;

                room_base |= 0x980;

                *(s32 *) (room_base + (room_index * 4)) = 0;
#endif
            }
            slot_index = func_800A1BD0(donor);
            {
#ifdef NON_MATCHING
                u8 *slot_page = D_80080000;
#else
                u8 *slot_page = (u8 *) 0x80080000;
#endif
                u8 *runtime_base;
                u8 *runtime_addr;
                ASM_KEEP_NV(slot_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                runtime_base = *(u8 **) (slot_page + 0x14A8);
                runtime_addr = (u8 *) (((s32) (slot_index << 0x10) >> 0xE) + (s32) runtime_base);

                ((S_800277F4_19 *)runtime_addr)->unk_D0 = 0;
            }
            func_8003DB4C(&D_800E3E48[(((S_800277F4_20 *)donor_runtime)->unk_03 & 0x1F) * 0x8C], 0x23);
            {
                register void *destroy_arg ASM_REG("$4") = donor_runtime;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                ASM_KEEP_NV(destroy_arg);
#ifdef NON_MATCHING
                D_800E3DF0[((S_800277F4_20 *)donor_runtime)->unk_03 & 0x1F] = 0;
#else
                {
                    u32 dead_base = 0x800E0000;
                    s32 dead_index;
                    ASM_KEEP_NV(dead_base);
                    dead_index = ((S_800277F4_20 *)donor_runtime)->unk_03;
                    ASM_KEEP(dead_index);
                    dead_base += 0x3DF0;
                    ASM_KEEP_NV(dead_base);
                    *(u32 *) (dead_base + ((dead_index & 0x1F) * 4)) = 0;
                }
#endif
                func_80098B38(destroy_arg);
            }
            result_traits = ((S_800277F4_0 *)result)->unk_54;
            if ((result_traits & 0x800000) &&
                ((result_kind = ((S_800277F4_0 *)result)->unk_13) != 2) &&
                (result_kind != 0x39)) {
                ((S_800277F4_0 *)result)->unk_54 = (s32) (result_traits & 0xFF7FFFFF);
            }
            (*(u16 *)((u8 *)donor + -2)) = (u16) (((S_800277F4_8_pre *)donor)[-1].unk_12 | 0x8000);
            global_flags = *(s32 *) (D_80080000 + 0x14A0);
            global_flags |= 0x8000;
            *(s32 *) (D_80080000 + 0x14A0) = global_flags;
            return result;
        }
        return result;
    }
    return result;
}
