#include "common.h"
#include "dungeon/item.h"
#include "dungeon/actor/effect.h"
#include "dungeon/menu.h"
#include "dungeon/actor/state.h"
struct State;

extern s32 poison_status_label[];
extern u8 poisoned_message[];
extern u8 poison_failed_message[];

/* Attempt to apply a status effect to the target and report success or failure. */
s32 try_apply_status_effect(void *target, s16 chance, s16 duration) {
    if (roll_poison_effect(target, chance, duration) != 0) {
        adjust_source_value_and_finalize(target, poisoned_message);
        if (*((u8 *)target + 0x13) == 0) {
            wrap_position_and_set_state_value(poison_status_label[0]);
        }
        return 1;
    }

    adjust_source_value_and_finalize(target, poison_failed_message);
    return 0;
}
