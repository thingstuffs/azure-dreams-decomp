#include "common.h"
#include "m2c_compat.h"
#include "dungeon/item/message.h"
#include "dungeon/actor/state.h"
#include "dungeon/data.h"
extern u8 electric_shock_ability_text[9];
extern u8 fusion_period[];
extern u8 ability_list_heading_text[];
extern u8 quick_ability_text[];
extern u8 hp_increased_ability_text[];
extern u8 mp_increased_ability_text[];
extern u8 strength_increased_ability_text[];
extern u8 hard_ability_text[];
extern u8 magic_attack_increased_ability_text[];
extern u8 mp_consumption_decreased_ability_text[];
extern u8 brainwash_proof_ability_text[];
extern u8 rustproof_ability_text[];
extern u8 sleep_proof_ability_text[];
extern u8 confusion_proof_ability_text[];
extern u8 blinder_proof_ability_text[];
extern u8 paralysis_proof_ability_text[];
extern u8 poison_proof_ability_text[];
extern u8 spell_proof_ability_text[];
extern u8 atrocious_ability_text[];
extern u8 attack_down_resist_ability_text[];
extern u8 growth_promoted_ability_text[];
/* Build the status-effect name list for the object's 0x54 flag word, comma-separated; returns the fallback when no flag is set. */
void *build_status_effect_name_list(void *obj, void *fallback)
{
    void *text;
    s32 count;
    void *result;
    void *saved_fallback;
    count = 0;
    saved_fallback = fallback;
    text = expand_text_control_codes(ability_list_heading_text, fallback);
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 1) {
        text = expand_text_control_codes(quick_ability_text, write_text_byte_and_advance(0xA, text));
        count = 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 2) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(hp_increased_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 4) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(mp_increased_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 8) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(strength_increased_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(hard_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(growth_promoted_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x80) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(magic_attack_increased_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(mp_consumption_decreased_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x8000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(electric_shock_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x100000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(brainwash_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(rustproof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x02000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(sleep_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x04000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(confusion_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x08000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(blinder_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x10000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(paralysis_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x20000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(poison_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x40000000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(spell_proof_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x200000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(atrocious_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((*((s32 *) (((s8 *) obj) + 0x54))) & 0x4000) {
        if ((count << 0x10) != 0) {
            text = expand_text_control_codes(status_name_separator, text);
        }
        text = expand_text_control_codes(attack_down_resist_ability_text, write_text_byte_and_advance(0xA, text));
        count += 1;
    }
    if ((count << 0x10) != 0) {
        result = expand_text_control_codes(fusion_period, text);
    }
    else {
        result = saved_fallback;
    }
    return result;
}
