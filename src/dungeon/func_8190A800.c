#include "modules/dungeon_ovl_192a800.h"
#include "common.h"


extern s32 dungeonTryTriggerTargetRecordEffect(void *entity, s32 flags);
extern s32 randomDungeonRange16(s32 bound_a, s32 bound_b);
extern s32 lowerEntityLevel(void *entity_data, s32 show_message);
extern void dungeonAdjustSourceValueAndFinalize(void *context, void *source);
extern void createActorValuePopup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern const u8 D_80024004[];


/* Runs action 0x53 on the target after state and threshold checks. */
void func_800240AC(void *target, s32 threshold_arg, void *owner_context) {
    s32 value_index;
    s32 threshold;

    if (dungeonTryTriggerTargetRecordEffect(target, 4) != 0) {
        return;
    }

    value_index = (s16)(randomDungeonRange16(0, ((u8 *)target)[3]) - 16);
    threshold = threshold_arg & 0xFF;
    if (value_index < threshold) {
        if (lowerEntityLevel(target, 1) != 0) {
            return;
        }
    } else if (threshold == 0xFF) {
        if (lowerEntityLevel(target, 1) != 0) {
            return;
        }
    }

    dungeonAdjustSourceValueAndFinalize(target, D_80024004);
    createActorValuePopup(0x53, target, -1, 1);
}
