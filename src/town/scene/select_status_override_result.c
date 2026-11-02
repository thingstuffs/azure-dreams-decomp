#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern u8 D_800181C8[];
extern u8 D_8001832C[];
extern u8 D_80019425[];
extern u8 D_80019915[];

/* Selects a result for the object, using its status to choose an override. */
void *select_status_override_result(void *object, s32 unused, s32 mode)
{
    void *base;
    void *result;

    base = D_800181C8;
    result = apply_entry_position(base, D_8001832C, object, mode);
    if (resolve_entry_flag(base, object, mode) != 0) {
        if (get_script_flag_mask(*(s16 *)((u8 *)object + 0x18)) != 0) {
            result = D_80019915;
        } else {
            result = D_80019425;
        }
    }
    return result;
}
