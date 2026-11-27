#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

extern u8 status_override_response_entries[];
extern u8 status_override_context[];
extern u8 status_flag_clear_response[];
extern u8 status_flag_set_response[];

/* Selects a result for the object, using its status to choose an override. */
void *select_status_override_result(TownObjectSet *object, s32 unused, s32 mode)
{
    void *base;
    void *result;

    base = status_override_response_entries;
    result = apply_entry_position(base, status_override_context, object, mode);
    if (resolve_entry_flag(base, object, mode) != 0) {
        if (get_script_flag_mask(object->entry_flag) != 0) {
            result = status_flag_set_response;
        } else {
            result = status_flag_clear_response;
        }
    }
    return result;
}
