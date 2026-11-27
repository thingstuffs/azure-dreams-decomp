#include "common.h"
#include "dungeon/item.h"
#include "dungeon/actor/effect.h"
#include "dungeon/menu.h"
struct State;

extern s32 blind_status_label;
extern u8 blind_failed_message[];
extern u8 blinded_message[];

/* Attempt to apply a status effect and display the result. */
s32 try_apply_blind_effect(void *entity, s16 chance, s16 effect_value) {
    if (roll_blind_effect(entity, chance, effect_value) != 0) {
        adjust_source_value_and_finalize(entity, blinded_message);
        if (*((u8 *)entity + 0x13) == 0) {
            wrap_position_and_set_state_value(blind_status_label);
        }
        return 1;
    }
    if ((*(s32 *)((u8 *)entity + 0x1C) & 0x10) == 0) {
        adjust_source_value_and_finalize(entity, blind_failed_message);
    }
    return 0;
}
