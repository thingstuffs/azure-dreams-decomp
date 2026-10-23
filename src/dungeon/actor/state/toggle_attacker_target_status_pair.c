#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"

extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 clear_byte_and_advance(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern s32 adjust_source_value_and_finalize(void *, void *);
extern s32 set_or_clear_actor_status_slot(void *, s32, s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern s32 generate_random_value(void);
extern s32 is_linked_entity_flagged_100000(void *);
extern s32 get_entity_effect_value(void *, s32);
extern void clear_slots_of_type(void *, s32);
extern s32 D_8008942C[];
extern s32 D_800E196F[];
extern s32 D_800E1987[];
extern s32 D_800E1996[];
extern s32 D_800E19AA[];

/* Toggle the 0xB/0xC status pair between attacker and target: roll the attacker's 0x3 chance plus its 0x11 bonus against 0x30, apply or clear the status on the target, and report whether the attempt did not fail. */
u32 toggle_attacker_target_status_pair(void *attacker, void *target) {
    s32 roll;
    s32 status;
    s32 shifted;
    s32 chance;
    s32 base_chance;

    status = -1;
    if (is_linked_entity_flagged_100000(target) != 0) {
        if (*(s32 *)((s8 *)target + 0x14) & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, &D_800E196F);
        }
        return 0;
    }
    roll = generate_random_value() & 0xFFFF;
    base_chance = *(u8 *)((s8 *)attacker + 0x11) >> 2;
    if (*(u8 *)((s8 *)attacker + 3) != 0) {
        chance = roll % *(u8 *)((s8 *)attacker + 3) + base_chance;
    } else {
        chance = base_chance;
    }
    if (chance >= 0x30) {
        if (*(s32 *)((s8 *)attacker + 0x1C) & 0x2000) {
            if (!(*(s32 *)((s8 *)target + 0x1C) & ACTOR_PLAYER_SIDE)) {
                if ((get_entity_effect_value(target, STATUS_BRAINWASH) << 0x10) != 0) {
                    clear_slots_of_type(target, STATUS_BRAINWASH);
                    status = 0;
                } else {
                    status = set_or_clear_actor_status_slot(target, STATUS_PLAYER_SIDE, 0x10);
                    if ((status << 0x10) < 0) {
                        goto block_error;
                    }
                    {
                        s32 session = get_unused_text_buffer();
                        s32 saved = session;
                        session = expand_text_control_codes(&D_800E1987, session);
                        clear_byte_and_advance(expand_text_control_codes(&D_8008942C, append_entity_display_text(target, session)));
                        display_text_with_fullwidth_adjustment(saved);
                    }
                }
            }
        } else if (*(s32 *)((s8 *)target + 0x1C) & ACTOR_PLAYER_SIDE) {
            if ((get_entity_effect_value(target, STATUS_PLAYER_SIDE) << 0x10) != 0) {
                clear_slots_of_type(target, STATUS_PLAYER_SIDE);
                status = 0;
            } else {
                status = set_or_clear_actor_status_slot(target, STATUS_BRAINWASH, 0x10);
                if ((status << 0x10) < 0) {
                    goto block_error;
                }
                adjust_source_value_and_finalize(target, &D_800E1996);
            }
        }
    }
    shifted = status << 0x10;
    if (shifted < 0) {
block_error:
        if (*(s32 *)((s8 *)target + 0x14) & ACTOR_PARTY_MEMBER) {
            adjust_source_value_and_finalize(target, &D_800E19AA);
        }
        shifted = status << 0x10;
    }
    shifted = status << 0x10;
    return (u32) ~(shifted >> 0x10) >> 0x1F;
}
