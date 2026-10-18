#include "modules/trap_effects_candidate.h"
#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CE748_0 {
    void * unk_00;
    u8 pad_04[0x13];
    u8 unk_17;
    u8 pad_18[0x10];
    s32 unk_28;
    u8 pad_2C[0x34];
    void * unk_60;
    void * unk_64;
    u8 pad_68[0x34];
    s16 unk_9C;
} S_800CE748_0;   /* record in update_trap_effect_grid; pointer addresses record offset 0x14 */

typedef struct S_800CE748_1 {
    u8 unk_00;
    u8 unk_01;
    s8 unk_02;
} S_800CE748_1;   /* firstEntry in update_trap_effect_grid */

typedef struct S_800CE748_2 {
    u8 unk_00;
    u8 pad_01[0x1];
    s8 unk_02;
} S_800CE748_2;   /* secondEntry in update_trap_effect_grid */

typedef struct S_800CE748_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CE748_3;   /* objectData in update_trap_effect_grid */



s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(u8 *src, u8 *dst);
void func_80099290(s8 *byte_ptr);
s32 write_text_byte_and_advance(s8 value, s8 *dest);
s32 apply_type_based_entry_adjustments(void *, s32);
extern s32 play_sound_if_enabled();
void display_text_with_fullwidth_adjustment(s8 *text);
extern void display_fixed_item_action_message();
s32 generate_random_value();
extern void * spawn_randomized_particle_burst();
s32 is_linked_object_flagged_10000(void *);

extern u8 D_800E1B76[18];
extern u8 D_800E1B87[18];
extern u8 D_800E1B99[18];
extern u8 D_800E1BAA[18];

s32 update_trap_effect_grid(void *record, s32 unused1, s32 unused2, s32 unused3) {
    s32 randomValueSecond;
    s32 randomValueFirst;
    s32 secondLookupValue;
    s32 firstLookupValue;
    s32 initialValue;
    s32 entryCode;
    s32 currentValue;
    s16 entryFlags;
    s32 triggerFlags;
    s32 entryValue;
    S_800CE748_1 *firstEntry;
    S_800CE748_2 *secondEntry;
    S_800CE748_3 *objectData;

    triggerFlags = 0;
    entryFlags = 0;
    if (is_linked_object_flagged_10000(record) == 0) {
        s16 probability;
        s32 random_mod;
        firstEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60;
        if (firstEntry != NULL) {

            entryFlags = 1;
            if (firstEntry->unk_01 == 0xF) {
                s32 is_one;

                is_one = firstEntry->unk_00 == 1;
                entryFlags = is_one;
            }
            if (D_800E3D40 == 0) {
                                /* garbage-passthru: a1/a3 are residue from is_linked_object_flagged_10000, without a defined C value. */
                randomValueFirst = generate_random_value() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueFirst % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 1)) {
                    if (firstEntry->unk_02 >= -0x62) {
                        firstEntry->unk_02 = (s8) ((u8) firstEntry->unk_02 - 1);
                    }
                }
                triggerFlags = 1;
            }
        }
        secondEntry = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64;
        if (secondEntry != NULL) {

            entryValue = secondEntry->unk_00;
            entryCode = entryValue & 0xFF;
            if ((entryCode == 1) || (entryCode == 7) || (((u32) (entryValue - 2) < 2U) != 0)) {
                entryFlags |= 2;
            }
            if (D_800E3D40 == 0) {
                                /* garbage-passthru: a1/a3 remain residue from earlier calls. */
                randomValueSecond = generate_random_value() & 0xFFFF;
                if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17 != 0) {
                    random_mod = randomValueSecond % ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_17;
                    probability = random_mod;
                } else {
                    probability = 0;
                }
            } else {
                probability = 0;
            }
            if (probability < 0x40) {
                if (!(entryFlags & 2)) {
                    if (secondEntry->unk_02 >= -0x62) {
                        secondEntry->unk_02 = (s8) ((u8) secondEntry->unk_02 - 1);
                    }
                }
                triggerFlags |= 2;
            }
        }
    }
    if (((S_800CE748_0 *)((u8 *)record - 0x14))->unk_28 & 0x4000) {
        if ((triggerFlags << 0x10) == 0) {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            display_fixed_item_action_message();
        } else {
                        /* garbage-passthru: a3 remains residue from earlier calls. */
            initialValue = get_unused_text_buffer();
            currentValue = initialValue;
            if (triggerFlags & 1) {
                firstLookupValue = apply_type_based_entry_adjustments(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_60, currentValue);
                {

                    if (!(entryFlags & 1)) {
                        currentValue = expand_text_control_codes(D_800E1B76, firstLookupValue);
                    } else {
                        currentValue = expand_text_control_codes(D_800E1B87, firstLookupValue);
                    }
                }
                if (triggerFlags & 2) {
                    currentValue = write_text_byte_and_advance(0xA, currentValue);
                }
            }
            if (triggerFlags & 2) {
                secondLookupValue = apply_type_based_entry_adjustments(((S_800CE748_0 *)((u8 *)record - 0x14))->unk_64, currentValue);
                {

                    if (!(entryFlags & 2)) {
                        currentValue = expand_text_control_codes(D_800E1B99, secondLookupValue);
                    } else {
                        currentValue = expand_text_control_codes(D_800E1BAA, secondLookupValue);
                    }
                }
            }
            func_80099290(currentValue);
            display_text_with_fullwidth_adjustment(initialValue);
        }
    }
    if ((triggerFlags << 0x10) != 0) {
        objectData = ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_00;
        if (!(objectData->unk_14 & 0x8000)) {
            spawn_randomized_particle_burst((objectData->unk_24 << 6) | 0x20, (objectData->unk_25 << 6) | 0x20,
                ((S_800CE748_0 *)((u8 *)record - 0x14))->unk_9C, 0xC0C040, 0x20, 0);
            play_sound_if_enabled(0x615);
        }
    }
    return 1;
}
