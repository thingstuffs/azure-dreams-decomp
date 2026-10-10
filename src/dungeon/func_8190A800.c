#include "modules/dungeon_ovl_192a800.h"
#include "common.h"


extern s32 func_8009D218(void *entity, s32 flags);
extern s32 func_800A6DA4(s32 bound_a, s32 bound_b);
extern s32 func_800A2424(void *entity_data, s32 show_message);
extern void func_80099844(void *context, void *source);
extern void func_800B4C7C(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern const u8 D_80024004[];


/* Runs action 0x53 on the target after state and threshold checks. */
void func_800240AC(void *target, s32 threshold_arg, void *owner_context) {
    s32 value_index;
    s32 threshold;

    if (func_8009D218(target, 4) != 0) {
        return;
    }

    value_index = (s16)(func_800A6DA4(0, ((u8 *)target)[3]) - 16);
    threshold = threshold_arg & 0xFF;
    if (value_index < threshold) {
        if (func_800A2424(target, 1) != 0) {
            return;
        }
    } else if (threshold == 0xFF) {
        if (func_800A2424(target, 1) != 0) {
            return;
        }
    }

    func_80099844(target, D_80024004);
    func_800B4C7C(0x53, target, -1, 1);
}
